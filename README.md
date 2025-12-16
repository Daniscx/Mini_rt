
# miniRT

A CPU raytracer written in C for the 42 school curriculum. Renders 3D scenes with spheres, planes, and cylinders using the MinilibX graphics library.

## Features

- Real-time navigation with keyboard and mouse
- Ray-sphere, ray-plane, and ray-cylinder intersections
- Ambient and diffuse lighting with hard shadows
- Multiple light sources support
- Dual resolution mode (low-res navigation, high-res screenshots)
- Scene file parser (.rt format)

## Build

```bash
make        # Compile project
make clean  # Remove object files
make fclean # Full cleanup
make re     # Recompile from scratch
```

## Usage

```bash
./miniRT <scene_file.rt>
./miniRT scenes/showcase.rt
```

## Scene File Format (.rt)

```
# Comment
A <ratio> <R,G,B>                      # Ambient light
C <x,y,z> <nx,ny,nz> <fov>             # Camera
L <x,y,z> <brightness> <R,G,B>         # Point light
sp <x,y,z> <diameter> <R,G,B>          # Sphere
pl <x,y,z> <nx,ny,nz> <R,G,B>          # Plane
cy <x,y,z> <nx,ny,nz> <d> <h> <R,G,B>  # Cylinder
```

### Parameter Ranges
- Ambient ratio: 0.0 - 1.0
- Light brightness: 0.0 - 1.0
- FOV: 0 - 180 degrees
- RGB: 0 - 255

## Requirements

- Linux with X11
- GCC compiler
- Make

---

La funcion de "M" no funciona tras el reescalado a mucha resolucion y vuelta a la normal D:

---
