
# miniRT

Ray tracer en C usando MinilibX - Proyecto 42 Madrid

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
