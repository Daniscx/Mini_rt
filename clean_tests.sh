#!/bin/bash

# Colors
RED='\033[0;31m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

echo -e "${CYAN}Limpiando directorios de tests...${NC}"

# Limpiar outs
if [ -d "outs" ]; then
    echo -e "${YELLOW}Eliminando outs/${NC}"
    rm -rf outs/
fi

# Limpiar outs_valgrind
if [ -d "outs_valgrind" ]; then
    echo -e "${YELLOW}Eliminando outs_valgrind/${NC}"
    rm -rf outs_valgrind/
fi

echo -e "${CYAN}✓ Limpieza completada${NC}"
