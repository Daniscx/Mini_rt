# miniRT - Error Testing Suite

Scripts automáticos para probar todos los casos de error del proyecto miniRT.

## Archivos

- **run_all_tests.sh** - 🌟 **Script principal** - Ejecuta todos los tests de forma interactiva
- **test_errors.sh** - Script de testing normal que prueba todos los casos de error
- **test_valgrind.sh** - Script que ejecuta los mismos tests con valgrind para detectar memory leaks
- **outs/** - Directorio donde se guardan los resultados del test_errors.sh
- **outs_valgrind/** - Directorio donde se guardan los resultados del test_valgrind.sh

## Inicio Rápido

### Opción 1: Script Todo-en-Uno (Recomendado)

```bash
./run_all_tests.sh
```

Este script ejecuta:
1. Compilación automática de miniRT
2. Todos los tests de manejo de errores
3. Te pregunta si deseas ejecutar tests de valgrind
4. Muestra un resumen completo al final

### Opción 2: Scripts Individuales

## Uso

### Testing Normal

```bash
./test_errors.sh
```

Este script:
- Compila automáticamente si es necesario
- Prueba **todas** las escenas inválidas en `scenes/invalid_scenes/`
- Prueba casos especiales:
  - Archivos sin extensión `.rt`
  - Archivos que no existen
  - Directorios en lugar de archivos
  - Sin argumentos
  - Demasiados argumentos
  - Archivos vacíos
  - Archivos sin permisos de lectura
  - Paths demasiado largos
- Guarda cada resultado en `outs/XXX_test_name.out`
- Genera un resumen en `outs/test_summary.log`
- Muestra estadísticas al final

### Testing con Valgrind

```bash
./test_valgrind.sh
```

Este script:
- Ejecuta los mismos tests pero con `valgrind --leak-check=full`
- Detecta memory leaks (definitely lost, indirectly lost, possibly lost)
- Detecta invalid reads/writes
- Guarda logs de valgrind en `outs_valgrind/XXX_test_name_valgrind.log`
- Guarda outputs en `outs_valgrind/XXX_test_name.out`
- Genera un resumen en `outs_valgrind/valgrind_summary.log`

**Nota**: Requiere tener valgrind instalado:
```bash
sudo apt-get install valgrind
```

## Interpretación de Resultados

### test_errors.sh

- ✓ **PASS** (verde) - El programa detectó el error correctamente (exit code ≠ 0)
- ✗ **FAIL** (rojo) - El programa NO detectó el error (exit code = 0)

Un test **pasa** cuando el programa rechaza correctamente la entrada inválida.

### test_valgrind.sh

- ✓ **NO MEMORY LEAKS** (verde) - No se detectaron fugas de memoria
- ✗ **MEMORY LEAKS DETECTED** (rojo) - Se detectaron fugas de memoria
  - **Definitely lost**: Memoria perdida que debe ser corregida
  - **Indirectly lost**: Memoria perdida indirectamente
  - **Possibly lost**: Posibles fugas (pueden ser falsos positivos)
  - **Still reachable**: Memoria accesible al salir (generalmente no crítico)

## Estructura de Outputs

### Archivo de output individual (outs/XXX_test_name.out)

```
========================================
TEST: test_name
FILE: path/to/file.rt
DESCRIPTION: Descripción del test
========================================

[Salida del programa]

EXIT CODE: 1
RESULT: PASS - Error detectado correctamente
```

### Archivo de resumen (outs/test_summary.log)

```
[001] invalid_all_letters                    PASS
[002] invalid_all                            PASS
[003] invalid_ambience                       PASS
...
========================================
RESUMEN FINAL
========================================
Total de tests: 40
Tests pasados:  38
Tests fallados: 2
Porcentaje:     95%
```

## Añadir Nuevos Tests

Para añadir nuevos casos de error:

1. Añade archivos `.rt` inválidos en `scenes/invalid_scenes/`
2. Los scripts los detectarán automáticamente
3. O edita los scripts para añadir casos especiales personalizados

## Tips

- Ejecuta `test_errors.sh` primero para verificar el manejo de errores
- Ejecuta `test_valgrind.sh` después para verificar memory leaks
- Los tests con valgrind son más lentos (timeout de 10s vs 2s)
- Revisa los archivos `.out` individuales para ver detalles de cada test
- Los archivos `_valgrind.log` contienen el output completo de valgrind

## Limpieza

```bash
# Limpiar outputs de tests normales
rm -rf outs/

# Limpiar outputs de valgrind
rm -rf outs_valgrind/

# Limpiar todo
rm -rf outs/ outs_valgrind/
```

## Escenas de Error Incluidas

El directorio `scenes/invalid_scenes/` contiene escenas que prueban:

- Valores fuera de rango (colores, ratios, FOV, brightness)
- Formatos incorrectos (colores, posiciones, vectores)
- Argumentos faltantes
- Múltiples elementos únicos (ambient, camera, light)
- Elementos desconocidos
- Valores no numéricos (letras en lugar de números)
- Normales fuera de rango
- Diámetros/alturas no válidas

**Total**: ~30+ escenas inválidas + casos especiales
