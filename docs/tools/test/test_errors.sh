#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

PROGRAM="./miniRT"
INVALID_SCENES_DIR="scenes/invalid_scenes"
OUTPUT_DIR="outs"
LOG_FILE="${OUTPUT_DIR}/test_summary.log"

# Crear directorio de outputs
mkdir -p "${OUTPUT_DIR}"
rm -f "${LOG_FILE}"

echo -e "${CYAN}========================================${NC}"
echo -e "${CYAN}  miniRT Error Testing Suite${NC}"
echo -e "${CYAN}========================================${NC}"
echo ""

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
passed_tests=0

# Función para ejecutar test
run_test() {
    local test_name="$1"
    local test_file="$2"
    local description="$3"

    total_tests=$((total_tests + 1))
    local output_file="${OUTPUT_DIR}/$(printf '%03d' ${total_tests})_${test_name}.out"

    echo -e "${BLUE}[Test ${total_tests}]${NC} ${description}"
    echo "========================================" >> "${output_file}"
    echo "TEST: ${test_name}" >> "${output_file}"
    echo "FILE: ${test_file}" >> "${output_file}"
    echo "DESCRIPTION: ${description}" >> "${output_file}"
    echo "========================================" >> "${output_file}"
    echo "" >> "${output_file}"

    # Ejecutar el programa y capturar salida
    timeout 2s ${PROGRAM} "${test_file}" >> "${output_file}" 2>&1
    local exit_code=$?

    echo "" >> "${output_file}"
    echo "EXIT CODE: ${exit_code}" >> "${output_file}"

    # Verificar que falló (exit code != 0)
    if [ ${exit_code} -ne 0 ]; then
        echo -e "${GREEN}✓ PASS${NC} - El programa detectó el error correctamente"
        echo "RESULT: PASS - Error detectado correctamente" >> "${output_file}"
        passed_tests=$((passed_tests + 1))
    else
        echo -e "${RED}✗ FAIL${NC} - El programa NO detectó el error (exit code = 0)"
        echo "RESULT: FAIL - Error NO detectado" >> "${output_file}"
    fi
    echo ""

    # Agregar al log resumido
    printf "[%03d] %-40s %s\n" ${total_tests} "${test_name}" "$([ ${exit_code} -ne 0 ] && echo 'PASS' || echo 'FAIL')" >> "${LOG_FILE}"
}

echo -e "${YELLOW}=== Probando escenas inválidas del directorio ===${NC}"
echo ""

# Probar todas las escenas inválidas en el directorio
if [ -d "${INVALID_SCENES_DIR}" ]; then
    for scene_file in ${INVALID_SCENES_DIR}/*.rt; do
        if [ -f "${scene_file}" ]; then
            filename=$(basename "${scene_file}")
            run_test "${filename%.rt}" "${scene_file}" "Escena inválida: ${filename}"
        fi
    done
fi

echo -e "${YELLOW}=== Probando casos especiales ===${NC}"
echo ""

# Test: Archivo sin extensión .rt
run_test "no_extension" "scenes/invalid_scenes/invalid_all" "Archivo sin extensión .rt"

# Test: Archivo que no existe
run_test "nonexistent" "scenes/nonexistent_file.rt" "Archivo que no existe"

# Test: Directorio en lugar de archivo
run_test "is_directory" "scenes/invalid_scenes" "Directorio en lugar de archivo"

# Test: Sin argumentos
echo -e "${BLUE}[Test $((total_tests + 1))]${NC} Sin argumentos"
total_tests=$((total_tests + 1))
output_file="${OUTPUT_DIR}/$(printf '%03d' ${total_tests})_no_arguments.out"
echo "========================================" >> "${output_file}"
echo "TEST: no_arguments" >> "${output_file}"
echo "DESCRIPTION: Ejecutar sin argumentos" >> "${output_file}"
echo "========================================" >> "${output_file}"
echo "" >> "${output_file}"
timeout 2s ${PROGRAM} >> "${output_file}" 2>&1
exit_code=$?
echo "" >> "${output_file}"
echo "EXIT CODE: ${exit_code}" >> "${output_file}"
if [ ${exit_code} -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} - El programa detectó el error correctamente"
    echo "RESULT: PASS - Error detectado correctamente" >> "${output_file}"
    passed_tests=$((passed_tests + 1))
else
    echo -e "${RED}✗ FAIL${NC} - El programa NO detectó el error"
    echo "RESULT: FAIL - Error NO detectado" >> "${output_file}"
fi
echo ""
printf "[%03d] %-40s %s\n" ${total_tests} "no_arguments" "$([ ${exit_code} -ne 0 ] && echo 'PASS' || echo 'FAIL')" >> "${LOG_FILE}"

# Test: Demasiados argumentos
echo -e "${BLUE}[Test $((total_tests + 1))]${NC} Demasiados argumentos"
total_tests=$((total_tests + 1))
output_file="${OUTPUT_DIR}/$(printf '%03d' ${total_tests})_too_many_args.out"
echo "========================================" >> "${output_file}"
echo "TEST: too_many_args" >> "${output_file}"
echo "DESCRIPTION: Ejecutar con demasiados argumentos" >> "${output_file}"
echo "========================================" >> "${output_file}"
echo "" >> "${output_file}"
timeout 2s ${PROGRAM} scenes/test_mandatory.rt scenes/test_bonus.rt >> "${output_file}" 2>&1
exit_code=$?
echo "" >> "${output_file}"
echo "EXIT CODE: ${exit_code}" >> "${output_file}"
if [ ${exit_code} -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} - El programa detectó el error correctamente"
    echo "RESULT: PASS - Error detectado correctamente" >> "${output_file}"
    passed_tests=$((passed_tests + 1))
else
    echo -e "${RED}✗ FAIL${NC} - El programa NO detectó el error"
    echo "RESULT: FAIL - Error NO detectado" >> "${output_file}"
fi
echo ""
printf "[%03d] %-40s %s\n" ${total_tests} "too_many_args" "$([ ${exit_code} -ne 0 ] && echo 'PASS' || echo 'FAIL')" >> "${LOG_FILE}"

# Test: Crear archivo temporal vacío
temp_empty=$(mktemp --suffix=.rt)
run_test "empty_file" "${temp_empty}" "Archivo .rt vacío"
rm -f "${temp_empty}"

# Test: Crear archivo temporal sin extensión
temp_no_ext=$(mktemp)
echo "A 0.2 255,255,255" > "${temp_no_ext}"
run_test "no_rt_extension" "${temp_no_ext}" "Archivo con contenido pero sin .rt"
rm -f "${temp_no_ext}"

# Test: Archivo con permisos solo escritura (sin lectura)
temp_no_read=$(mktemp --suffix=.rt)
echo "A 0.2 255,255,255" > "${temp_no_read}"
chmod 000 "${temp_no_read}"
run_test "no_read_permission" "${temp_no_read}" "Archivo sin permisos de lectura"
chmod 644 "${temp_no_read}"
rm -f "${temp_no_read}"

# Test: Path muy largo
long_path=$(printf 'a/%.0s' {1..100})
run_test "path_too_long" "${long_path}file.rt" "Path extremadamente largo"

echo -e "${CYAN}========================================${NC}"
echo -e "${CYAN}  Resumen de Tests${NC}"
echo -e "${CYAN}========================================${NC}"
echo -e "Total de tests: ${BLUE}${total_tests}${NC}"
echo -e "Tests pasados:  ${GREEN}${passed_tests}${NC}"
echo -e "Tests fallados: ${RED}$((total_tests - passed_tests))${NC}"

if [ ${passed_tests} -eq ${total_tests} ]; then
    echo -e "${GREEN}¡Todos los tests pasaron correctamente!${NC}"
else
    echo -e "${YELLOW}Algunos tests fallaron. Revisa los archivos en ${OUTPUT_DIR}/${NC}"
fi

echo ""
echo -e "Resultados guardados en: ${CYAN}${OUTPUT_DIR}/${NC}"
echo -e "Resumen disponible en: ${CYAN}${LOG_FILE}${NC}"
echo ""

# Crear resumen final en el log
{
    echo ""
    echo "========================================"
    echo "RESUMEN FINAL"
    echo "========================================"
    echo "Total de tests: ${total_tests}"
    echo "Tests pasados:  ${passed_tests}"
    echo "Tests fallados: $((total_tests - passed_tests))"
    echo "Porcentaje:     $(( passed_tests * 100 / total_tests ))%"
} >> "${LOG_FILE}"
