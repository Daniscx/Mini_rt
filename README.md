
# miniRT

## 📖 About

"miniRT" is a project at 42 Madrid that involves creating a CPU-based raytracer written in C. This project introduces 3D computer graphics fundamentals, ray-object intersection mathematics, and teaches how to render photorealistic scenes with lighting, shadows, and multiple geometric primitives using the MiniLibX graphics library.

The goal is to implement a program that can parse scene description files and render 3D scenes with spheres, planes, cylinders, and cones, featuring real-time navigation, multiple light sources, and advanced features like textures and bump mapping.

## 🎯 Objectives

- Understanding and implementing ray-tracing algorithms
- Learning 3D mathematics: vectors, rays, and geometric intersections
- Managing pixel manipulation and image rendering with MiniLibX
- Implementing interactive event handling (keyboard, mouse navigation)
- Exploring lighting models: ambient, diffuse, and specular illumination
- Understanding shadow casting and multi-light rendering
- Scene file parsing and validation

## 📋 Features

<details>
<summary><strong>Core Features</strong></summary>

<br>

| Feature | Description |
|---------|-------------|
| **Ray-Tracing Engine** | CPU-based raytracer with configurable resolution |
| **Geometric Primitives** | Spheres, planes, cylinders, and cones with caps |
| **Lighting System** | Ambient light + multiple point lights with colors |
| **Hard Shadows** | Shadow rays for realistic shadow casting |
| **Scene Parser** | Custom `.rt` file format parser |
| **Real-time Navigation** | WASD movement + mouse look controls |
| **Dual Resolution** | Low-res for navigation, high-res for screenshots |
| **Object Selection** | Click to select and drag objects in the scene |

<br>

</details>

<details>
<summary><strong>Bonus Features</strong></summary>

<br>

| Feature | Description |
|---------|-------------|
| **Colored Lights** | RGB-configurable point light sources |
| **Specular Highlights** | Phong reflection model implementation |
| **Checkerboard Pattern** | Procedural checkerboard texture |
| **Texture Mapping** | PPM texture support for spheres |
| **Bump Mapping** | Normal perturbation for surface detail |
| **Cone Primitive** | Full cone support with base cap |

<br>

</details>

## 🚀 Installation & Structure

<details>
<summary><strong>📥 Compilation & Functionality</strong></summary>

<br>

## Build

```bash
make                    # Compile project without “color bleeding” mode
make cb                 # Compile with “color bleeding” mode
make re                 # Recompile from scratch without “color bleeding” mode
make test_mandatory     # Compile project without “color bleeding” mode and run the mandatory test scene
make test_bonus         # Compile project without “color bleeding” mode and run the bonus test scene
make clean              # Remove object files
make fclean             # Full cleanup
make clean_screenshots  # Delete all screenshots from <./screenshots/>
make fclean_screenshots # Delete all screenshots from <./screenshots/> and the <./screenshots/> directory
```

## Usage

```bash
./miniRT <scene_file>
./miniRT scenes/showcase.rt
```

### Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move camera forward/left/back/right |
| `Space` / `Shift` | Move camera up/down |
| `Arrow Keys` | Rotate camera view |
| `Mouse` | Look around (when captured) |
| `Left Click` | Select object / Capture mouse |
| `Right Click` | Release mouse |
| `P` | Take high-resolution screenshot |
| `ESC` | Exit program |

## Scene File Format (.rt)

Scene files use a simple text format to define cameras, lights, and objects:

```
# Comment line
A <ratio> <R,G,B>                           # Ambient light
C <x,y,z> <nx,ny,nz> <fov>                  # Camera
L <x,y,z> <brightness> <R,G,B>              # Point light

sp <x,y,z> <diameter> <R,G,B>               # Sphere
pl <x,y,z> <nx,ny,nz> <R,G,B>               # Plane
cy <x,y,z> <nx,ny,nz> <diameter> <h> <R,G,B> # Cylinder
co <x,y,z> <nx,ny,nz> <angle> <h> <R,G,B>   # Cone
```

### Parameter Ranges

| Parameter | Range | Description |
|-----------|-------|-------------|
| Ambient ratio | 0.0 - 1.0 | Intensity of ambient light |
| Light brightness | 0.0 - 1.0 | Point light intensity |
| FOV | 0 - 180 | Camera field of view in degrees |
| RGB | 0 - 255 | Color components |
| Normal vectors | -1.0 - 1.0 | Direction vectors (auto-normalized) |

### Bonus Identifiers

| Identifier | Description |
|------------|-------------|
| `plc` | Plane with checkerboard pattern |
| `spt` | Sphere with texture (requires texture path) |
| `spb` | Sphere with bump map |

## Example Scene

```
# Ambient light - soft white
A 0.2 255,255,255

# Camera position, direction, FOV
C 0,2,10 0,0,-1 60

# Lights
L -5,10,5 0.8 255,255,255
L 5,8,3 0.6 255,200,150

# Objects
sp 0,1,0 2 255,100,100        # Red sphere
pl 0,0,0 0,1,0 150,150,150    # Gray floor
cy -3,0,0 0,1,0 1 3 100,255,100  # Green cylinder
```

<br>

</details>

<details>
<summary><strong>📁 Project Structure</strong></summary>

<br>

```
miniRT/						# Project structure still to be defined
├── include/
├── linux-minilibx/
├── src/
├── scenes/
├── Makefile
└── README.md
```

<br>

</details>

## Key Learning Outcomes

The miniRT project teaches fundamental 3D graphics and raytracing concepts:

- **Vector Mathematics**: Operations with 3D vectors (dot product, cross product, normalization)
- **Ray-Object Intersection**: Mathematical solutions for ray-sphere, ray-plane, ray-cylinder intersections
- **Lighting Models**: Understanding ambient, diffuse, and specular components
- **Shadow Casting**: Implementing shadow rays to detect occlusions
- **Camera Systems**: Generating rays from camera through viewport pixels
- **Scene Management**: Parsing and storing complex 3D scene data
- **Real-time Graphics**: Balancing quality and performance for interactive rendering

## Technical Specifications

- **Language**: C (C90 standard)
- **Compiler**: cc with flags `-Wall -Wextra -Werror`
- **Graphics Library**: MiniLibX (X11-based)
- **Platform**: Linux with X11
- **Resolution**: 426x240 (navigation) / 4096x2160 (screenshots)
- **Color Depth**: 24-bit RGB
- **Memory Management**: Proper cleanup of all allocated resources

## Requirements

- Linux with X11
- GCC compiler
- Make
- X11 development libraries (`libx11-dev`, `libxext-dev`)

---

> [!NOTE]
> This project serves as a comprehensive introduction to ray-tracing and 3D computer graphics, demonstrating proficiency in mathematical visualization, geometric algorithms, and interactive graphics programming.
