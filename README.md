
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

## Controls

| Key | Action |
|-----|--------|
| W/S | Move forward/backward |
| A/D | Move left/right |
| Space/Shift | Move up/down |
| Arrow keys | Rotate camera |
| Mouse | Look around |
| P | High resolution render (5s) |
| ESC | Exit |

Multiple movement keys can be pressed simultaneously (e.g., W+A for diagonal movement).

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

## Raytracing Pipeline

1. Parse scene file into typed structures
2. For each pixel, cast ray from camera
3. Find closest intersection with scene objects
4. Calculate lighting (ambient + diffuse) with shadow checks
5. Write pixel color to image buffer
6. Display image via MinilibX

## Requirements

- Linux with X11
- GCC compiler
- Make

