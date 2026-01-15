#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

PROGRAM="./miniRT"
INVALID_SCENES_DIR="scenes/invalid_scenes"
OUTPUT_DIR="outs_valgrind"
LOG_FILE="${OUTPUT_DIR}/valgrind_summary.log"
VALGRIND_CMD="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file="

# Crear directorio de outputs
mkdir -p "${OUTPUT_DIR}"
rm -f "${LOG_FILE}"

echo -e "${MAGENTA}========================================${NC}"
echo -e "${MAGENTA}  miniRT Valgrind Memory Test Suite${NC}"
echo -e "${MAGENTA}========================================${NC}"
echo ""

# Verificar que valgrind está instalado
if ! command -v valgrind &> /dev/null; then
    echo -e "${RED}Error: valgrind no está instalado${NC}"
    echo -e "${YELLOW}Instala con: sudo apt-get install valgrind${NC}"
    exit 1
fi

# Verificar que el ejecutable existe
if [ ! -f "${PROGRAM}" ]; then
    echo -e "${RED}Error: ${PROGRAM} no encontrado. Compilando...${NC}"
    make
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error: Fallo la compilación${NC}"
        exit 1
    fi
fi

# Contador de tests
total_tests=0
no_leaks=0
has_leaks=0

# Función para ejecutar test con valgrind
run_valgrind_test() {
    local test_name="$1"
    local test_file="$2"
    local description="$3"

    total_tests=$((total_tests + 1))
    local valgrind_log="${OUTPUT_DIR}/$(printf '%03d' ${total_tests})_${test_name}_valgrind.log"
    local output_file="${OUTPUT_DIR}/$(printf '%03d' ${total_tests})_${test_name}.out"

    echo -e "${BLUE}[Test ${total_tests}]${NC} ${description}"
    echo "========================================" > "${output_file}"
    echo "TEST: ${test_name}" >> "${output_file}"
    echo "FILE: ${test_file}" >> "${output_file}"
    echo "DESCRIPTION: ${description}" >> "${output_file}"
    echo "========================================" >> "${output_file}"
    echo "" >> "${output_file}"

    # Ejecutar con valgrind
    echo -e "${CYAN}  Ejecutando valgrind...${NC}"
    timeout 10s ${VALGRIND_CMD}${valgrind_log} ${PROGRAM} "${test_file}" >> "${output_file}" 2>&1
    local exit_code=$?

    echo "" >> "${output_file}"
    echo "EXIT CODE: ${exit_code}" >> "${output_file}"
    echo "VALGRIND LOG: ${valgrind_log}" >> "${output_file}"

    # Analizar el log de valgrind
    if [ -f "${valgrind_log}" ]; then
        # Buscar leaks en el log
        local definitely_lost=$(grep "definitely lost:" "${valgrind_log}" | grep -oP '\d+(?= bytes)' | head -1)
        local indirectly_lost=$(grep "indirectly lost:" "${valgrind_log}" | grep -oP '\d+(?= bytes)' | head -1)
        local possibly_lost=$(grep "possibly lost:" "${valgrind_log}" | grep -oP '\d+(?= bytes)' | head -1)
        local still_reachable=$(grep "still reachable:" "${valgrind_log}" | grep -oP '\d+(?= bytes)' | head -1)

        # Defaults a 0 si no se encuentra
        definitely_lost=${definitely_lost:-0}
        indirectly_lost=${indirectly_lost:-0}
        possibly_lost=${possibly_lost:-0}
        still_reachable=${still_reachable:-0}

        local total_leaked=$((definitely_lost + indirectly_lost + possibly_lost))

        echo "" >> "${output_file}"
        echo "========================================" >> "${output_file}"
        echo "MEMORY ANALYSIS:" >> "${output_file}"
        echo "========================================" >> "${output_file}"
        echo "Definitely lost: ${definitely_lost} bytes" >> "${output_file}"
        echo "Indirectly lost: ${indirectly_lost} bytes" >> "${output_file}"
        echo "Possibly lost:   ${possibly_lost} bytes" >> "${output_file}"
        echo "Still reachable: ${still_reachable} bytes" >> "${output_file}"
        echo "Total leaked:    ${total_leaked} bytes" >> "${output_file}"

        if [ ${total_leaked} -eq 0 ]; then
            echo -e "${GREEN}  ✓ NO MEMORY LEAKS${NC}"
            echo "RESULT: NO LEAKS" >> "${output_file}"
            no_leaks=$((no_leaks + 1))
            printf "[%03d] %-40s %s (leaked: %d bytes)\n" ${total_tests} "${test_name}" "NO LEAKS" ${total_leaked} >> "${LOG_FILE}"
        else
            echo -e "${RED}  ✗ MEMORY LEAKS DETECTED${NC}"
            echo -e "${RED}    Definitely lost: ${definitely_lost} bytes${NC}"
            echo -e "${RED}    Indirectly lost: ${indirectly_lost} bytes${NC}"
            echo -e "${RED}    Possibly lost:   ${possibly_lost} bytes${NC}"
            echo "RESULT: LEAKS DETECTED" >> "${output_file}"
            has_leaks=$((has_leaks + 1))
            printf "[%03d] %-40s %s (leaked: %d bytes)\n" ${total_tests} "${test_name}" "HAS LEAKS" ${total_leaked} >> "${LOG_FILE}"
        fi

        # Buscar errores de memoria (invalid reads/writes)
        local invalid_reads=$(grep -c "Invalid read" "${valgrind_log}" 2>/dev/null || echo 0)
        local invalid_writes=$(grep -c "Invalid write" "${valgrind_log}" 2>/dev/null || echo 0)

        if [ ${invalid_reads} -gt 0 ] || [ ${invalid_writes} -gt 0 ]; then
            echo -e "${RED}  ⚠ MEMORY ERRORS DETECTED${NC}"
            echo -e "${RED}    Invalid reads:  ${invalid_reads}${NC}"
            echo -e "${RED}    Invalid writes: ${invalid_writes}${NC}"
            echo "" >> "${output_file}"
            echo "Invalid reads:  ${invalid_reads}" >> "${output_file}"
            echo "Invalid writes: ${invalid_writes}" >> "${output_file}"
        fi
    else
        echo -e "${RED}  ✗ Valgrind log no generado${NC}"
        echo "RESULT: ERROR - Log not generated" >> "${output_file}"
    fi
    echo ""
}

echo -e "${YELLOW}=== Probando escenas inválidas con valgrind ===${NC}"
echo ""

# Probar todas las escenas inválidas en el directorio
if [ -d "${INVALID_SCENES_DIR}" ]; then
    for scene_file in ${INVALID_SCENES_DIR}/*.rt; do
        if [ -f "${scene_file}" ]; then
            filename=$(basename "${scene_file}")
            run_valgrind_test "${filename%.rt}" "${scene_file}" "Escena inválida: ${filename}"
        fi
    done
fi

echo -e "${YELLOW}=== Probando casos especiales con valgrind ===${NC}"
echo ""

# Test: Archivo sin extensión .rt
run_valgrind_test "no_extension" "scenes/invalid_scenes/invalid_all" "Archivo sin extensión .rt"

# Test: Archivo que no existe
run_valgrind_test "nonexistent" "scenes/nonexistent_file.rt" "Archivo que no existe"

# Test: Directorio en lugar de archivo
run_valgrind_test "is_directory" "scenes/invalid_scenes" "Directorio en lugar de archivo"

# Test: Sin argumentos
echo -e "${BLUE}[Test $((total_tests + 1))]${NC} Sin argumentos"
total_tests=$((total_tests + 1))
valgrind_log="${OUTPUT_DIR}/$(printf '%03d' ${total_tests})_no_arguments_valgrind.log"
output_file="${OUTPUT_DIR}/$(printf '%03d' ${total_tests})_no_arguments.out"
echo "========================================" > "${output_file}"
echo "TEST: no_arguments" >> "${output_file}"
echo "DESCRIPTION: Ejecutar sin argumentos" >> "${output_file}"
echo "========================================" >> "${output_file}"
echo "" >> "${output_file}"
echo -e "${CYAN}  Ejecutando valgrind...${NC}"
timeout 10s ${VALGRIND_CMD}${valgrind_log} ${PROGRAM} >> "${output_file}" 2>&1

if [ -f "${valgrind_log}" ]; then
    definitely_lost=$(grep "definitely lost:" "${valgrind_log}" | grep -oP '\d+(?= bytes)' | head -1)
    indirectly_lost=$(grep "indirectly lost:" "${valgrind_log}" | grep -oP '\d+(?= bytes)' | head -1)
    possibly_lost=$(grep "possibly lost:" "${valgrind_log}" | grep -oP '\d+(?= bytes)' | head -1)
    definitely_lost=${definitely_lost:-0}
    indirectly_lost=${indirectly_lost:-0}
    possibly_lost=${possibly_lost:-0}
    total_leaked=$((definitely_lost + indirectly_lost + possibly_lost))

    if [ ${total_leaked} -eq 0 ]; then
        echo -e "${GREEN}  ✓ NO MEMORY LEAKS${NC}"
        no_leaks=$((no_leaks + 1))
        printf "[%03d] %-40s %s (leaked: %d bytes)\n" ${total_tests} "no_arguments" "NO LEAKS" ${total_leaked} >> "${LOG_FILE}"
    else
        echo -e "${RED}  ✗ MEMORY LEAKS DETECTED (${total_leaked} bytes)${NC}"
        has_leaks=$((has_leaks + 1))
        printf "[%03d] %-40s %s (leaked: %d bytes)\n" ${total_tests} "no_arguments" "HAS LEAKS" ${total_leaked} >> "${LOG_FILE}"
    fi
fi
echo ""

# Test: Crear archivo temporal vacío
temp_empty=$(mktemp --suffix=.rt)
run_valgrind_test "empty_file" "${temp_empty}" "Archivo .rt vacío"
rm -f "${temp_empty}"

# Test: Crear archivo temporal sin extensión
temp_no_ext=$(mktemp)
echo "A 0.2 255,255,255" > "${temp_no_ext}"
run_valgrind_test "no_rt_extension" "${temp_no_ext}" "Archivo con contenido pero sin .rt"
rm -f "${temp_no_ext}"

echo -e "${MAGENTA}========================================${NC}"
echo -e "${MAGENTA}  Resumen de Tests Valgrind${NC}"
echo -e "${MAGENTA}========================================${NC}"
echo -e "Total de tests:     ${BLUE}${total_tests}${NC}"
echo -e "Sin memory leaks:   ${GREEN}${no_leaks}${NC}"
echo -e "Con memory leaks:   ${RED}${has_leaks}${NC}"

if [ ${has_leaks} -eq 0 ]; then
    echo -e "${GREEN}¡Excelente! No se detectaron memory leaks${NC}"
else
    echo -e "${YELLOW}Se detectaron memory leaks en ${has_leaks} tests${NC}"
    echo -e "${YELLOW}Revisa los archivos .log en ${OUTPUT_DIR}/ para más detalles${NC}"
fi

echo ""
echo -e "Resultados guardados en: ${CYAN}${OUTPUT_DIR}/${NC}"
echo -e "Resumen disponible en: ${CYAN}${LOG_FILE}${NC}"
echo ""

# Crear resumen final en el log
{
    echo ""
    echo "========================================"
    echo "RESUMEN FINAL VALGRIND"
    echo "========================================"
    echo "Total de tests:     ${total_tests}"
    echo "Sin memory leaks:   ${no_leaks}"
    echo "Con memory leaks:   ${has_leaks}"
    if [ ${total_tests} -gt 0 ]; then
        echo "Porcentaje sin leaks: $(( no_leaks * 100 / total_tests ))%"
    fi
} >> "${LOG_FILE}"
