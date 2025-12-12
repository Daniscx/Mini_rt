
# miniRT

Ray tracer en C usando MinilibX - Proyecto 42 Madrid

## Estado del Proyecto

**En desarrollo** - Infraestructura básica completada

### ✅ Implementado
- Sistema de ventanas y renderizado con MinilibX
- Librería completa de operaciones vectoriales 3D
- Sistema de cámara con movimiento 6DOF (6 grados de libertad)
- Controles de teclado para navegación y rotación
- Parser parcial de archivos .rt (ambient light y camera)
- Estructura de proyecto y Makefile

### 🚧 En desarrollo
- Parser completo de elementos (luces, objetos)
- Sistema de ray tracing
- Intersección con objetos (esferas, planos, cilindros)
- Iluminación y sombreado

## Requisitos

- GCC/Clang
- MinilibX (incluida en el proyecto)
- X11, Xext
- Make
- libm, libz

## Compilación y Uso

```bash
make
./miniRT scenes/test.rt
```

Para limpiar:
```bash
make clean   # Eliminar objetos
make fclean  # Limpieza completa
make re      # Recompilar
```

## Controles

| Tecla | Acción |
|-------|--------|
| ESC | Salir del programa |
| W | Mover adelante |
| S | Mover atrás |
| A | Mover izquierda |
| D | Mover derecha |
| SPACE | Mover arriba |
| SHIFT | Mover abajo |
| ← | Rotar cámara izquierda |
| → | Rotar cámara derecha |
| ↑ | Rotar cámara arriba |
| ↓ | Rotar cámara abajo |

## Estructura del Proyecto

```
miniRT/
├── src/
│   ├── main.c              # Punto de entrada
│   ├── axu_minirt/         # Sistema MLX
│   │   ├── init.c          # Inicialización MLX y ventana
│   │   ├── events.c        # Manejo de eventos teclado/cierre
│   │   └── camera.c        # Movimiento y rotación de cámara
│   ├── math/               # Matemáticas vectoriales
│   │   ├── vec3.c          # Operaciones básicas de vectores
│   │   └── vec3_utils.c    # Producto cruz, normalización
│   ├── render/             # Sistema de renderizado
│   │   └── render.c        # Renderizado de escena
│   ├── parse/              # Parser archivos .rt
│   │   └── parse.c         # Lectura y validación de escenas
│   ├── scene/              # Gestión de escenas
│   │   └── scene.c         # Constructor/destructor de escenas
│   └── aux_libft/          # Librería de utilidades
├── include/
│   └── minirt.h           # Definiciones y prototipos
├── scenes/                 # Archivos de escena .rt
├── linux-minilibx/         # Librería gráfica MinilibX
└── Makefile
```

## Formato de Archivos .rt

Los archivos de escena definen la configuración del mundo 3D:

```
A 0.2 255,255,255
C 0,0,-5 0,0,1 60
L -10,10,-10 0.7 255,255,255
sp 0,0,10 5 255,0,0
pl 0,-5,0 0,1,0 128,128,128
cy 2,0,10 0,1,0 2 10 0,255,0
```

### Especificación de Elementos

| Elemento | Formato | Descripción |
|----------|---------|-------------|
| **A** | `ratio R,G,B` | Luz ambiental: ratio [0.0-1.0], color RGB [0-255] |
| **C** | `x,y,z vx,vy,vz fov` | Cámara: posición, vector dirección [-1,1], FOV [0-180] |
| **L** | `x,y,z brightness R,G,B` | Luz puntual: posición, brillo [0.0-1.0], color RGB |
| **sp** | `x,y,z diameter R,G,B` | Esfera: centro, diámetro, color RGB |
| **pl** | `x,y,z nx,ny,nz R,G,B` | Plano: punto, vector normal [-1,1], color RGB |
| **cy** | `x,y,z nx,ny,nz diameter height R,G,B` | Cilindro: centro, eje [-1,1], diámetro, altura, color |

### Reglas
- Un solo elemento de Luz Ambiental (A)
- Una sola Cámara (C)
- Múltiples luces y objetos permitidos
- Coordenadas: formato `x,y,z` sin espacios
- Colores RGB: valores enteros [0-255]
- Vectores normalizados: componentes en rango [-1,1]

## Funciones Implementadas

### Operaciones Vectoriales (src/math/)
- `vec3_new()` - Crear vector 3D
- `vec3_add()` - Suma de vectores
- `vec3_sub()` - Resta de vectores
- `vec3_scale()` - Multiplicación escalar
- `vec3_dot()` - Producto escalar
- `vec3_cross()` - Producto vectorial
- `vec3_normalize()` - Normalización de vectores
- `vec3_length()` - Magnitud del vector

### Sistema de Cámara (src/axu_minirt/camera.c)
- `camera_init()` - Inicialización con valores por defecto
- `camera_move()` - Traslación en espacio 3D
- `camera_rotate()` - Rotación yaw/pitch

### Sistema de Renderizado (src/render/render.c)
- `render_scene()` - Renderiza la escena actual (temporal: gradiente)

## Compilación Técnica

El proyecto usa un sistema de compilación modular:
- Compilación incremental con barra de progreso
- Objetos separados para miniRT y libft
- Linking automático con MinilibX
- Flags: `-Wall -Wextra -Werror`

## Notas de Desarrollo

El proyecto actualmente renderiza un gradiente de fondo. Los próximos pasos incluyen:
1. Completar el parser de todos los elementos .rt
2. Implementar ray tracing básico
3. Calcular intersecciones con objetos geométricos
4. Aplicar modelo de iluminación Phong/Lambert
5. Gestión de múltiples objetos y luces

## Subject

[miniRT.pdf](https://github.com/mcombeau/miniRT/blob/main/doc/en.subject.pdf)

---
