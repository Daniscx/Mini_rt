
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

## Test Scenes

The `scenes/` directory contains test files for each evaluation criterion:

| File | Test |
|------|------|
| 01_sphere.rt | Sphere at origin |
| 02_plane.rt | Plane at z=0 |
| 03_cylinder.rt | Cylinder along Y axis |
| 04_translation.rt | Object translation |
| 05_rotation.rt | Cylinder rotation |
| 06_intersecting.rt | Intersecting objects |
| 07_multiple.rt | Multiple objects of same type |
| 08_camera_x.rt | Camera along X axis |
| 09_camera_y.rt | Camera along Y axis |
| 10_camera_z.rt | Camera along Z axis |
| 11_camera_random.rt | Camera at arbitrary position |
| 12_brightness_side.rt | Side lighting |
| 13_brightness_translated.rt | Lighting on translated object |
| 14_shadow.rt | Shadow casting |
| 15_complex.rt | Complex scene with shadows |
| showcase.rt | High-res demo scene |

## Project Structure

```
miniRT/
├── include/minirt.h     # Main header
├── src/
│   ├── minirt.c         # Entry point
│   ├── axu_minirt/      # MLX init, events, camera
│   ├── math/            # Vector operations
│   ├── ray/             # Ray casting, intersections
│   ├── light/           # Lighting calculations
│   ├── render/          # Render loop
│   ├── scene/           # Scene loading
│   ├── parse/           # Parser utilities
│   └── aux_libft/       # Custom libft
├── linux-minilibx/      # MinilibX library
└── scenes/              # Test scenes
```

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

## Author

42 Madrid student project
