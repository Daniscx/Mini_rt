#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
BOLD='\033[1m'
NC='\033[0m' # No Color

clear

echo -e "${BOLD}${CYAN}"
echo "╔════════════════════════════════════════════╗"
echo "║                                            ║"
echo "║     miniRT Complete Testing Suite          ║"
echo "║                                            ║"
echo "╚════════════════════════════════════════════╝"
echo -e "${NC}"
echo ""

# Verificar que los scripts existen
if [ ! -f "test_errors.sh" ]; then
    echo -e "${RED}Error: test_errors.sh no encontrado${NC}"
    exit 1
fi

if [ ! -f "test_valgrind.sh" ]; then
    echo -e "${RED}Error: test_valgrind.sh no encontrado${NC}"
    exit 1
fi

# Compilar el proyecto
echo -e "${YELLOW}[1/3] Compilando miniRT...${NC}"
make
if [ $? -ne 0 ]; then
    echo -e "${RED}Error: Fallo la compilación${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Compilación exitosa${NC}"
echo ""

# Ejecutar test de errores
echo -e "${YELLOW}[2/3] Ejecutando tests de manejo de errores...${NC}"
echo -e "${CYAN}═══════════════════════════════════════════${NC}"
./test_errors.sh
error_exit=$?
echo ""

# Preguntar si desea ejecutar valgrind
echo -e "${YELLOW}[3/3] Tests con Valgrind${NC}"
echo -e "${CYAN}═══════════════════════════════════════════${NC}"
echo -e "${MAGENTA}Los tests con valgrind pueden tardar varios minutos...${NC}"
echo -e -n "${BOLD}¿Deseas ejecutar los tests de valgrind? (s/N): ${NC}"
read -r response

if [[ "$response" =~ ^[sS]$ ]]; then
    echo ""
    echo -e "${CYAN}Ejecutando tests con valgrind...${NC}"
    echo -e "${CYAN}═══════════════════════════════════════════${NC}"
    ./test_valgrind.sh
    valgrind_exit=$?
    echo ""
else
    echo -e "${YELLOW}Tests de valgrind omitidos${NC}"
    echo ""
fi

# Resumen final
echo -e "${BOLD}${CYAN}"
echo "╔════════════════════════════════════════════╗"
echo "║          Resumen de Tests                  ║"
echo "╚════════════════════════════════════════════╝"
echo -e "${NC}"

# Mostrar resumen de test_errors.sh
if [ -f "outs/test_summary.log" ]; then
    echo -e "${BOLD}${BLUE}Tests de Manejo de Errores:${NC}"
    tail -5 outs/test_summary.log | grep -E "Total|pasados|fallados|Porcentaje"
    echo ""
fi

# Mostrar resumen de valgrind si se ejecutó
if [ -f "outs_valgrind/valgrind_summary.log" ]; then
    echo -e "${BOLD}${MAGENTA}Tests de Valgrind (Memory Leaks):${NC}"
    tail -5 outs_valgrind/valgrind_summary.log | grep -E "Total|Sin|Con|Porcentaje"
    echo ""
fi

echo -e "${CYAN}═══════════════════════════════════════════${NC}"
echo -e "${BOLD}Archivos de resultados:${NC}"
echo -e "  ${GREEN}•${NC} Error tests:    ${CYAN}outs/test_summary.log${NC}"
if [ -f "outs_valgrind/valgrind_summary.log" ]; then
    echo -e "  ${GREEN}•${NC} Valgrind tests: ${CYAN}outs_valgrind/valgrind_summary.log${NC}"
fi
echo ""
echo -e "${YELLOW}Ver TESTING_README.md para más información${NC}"
echo ""
