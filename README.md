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
make                    	# Compile project without “color bleeding” mode
make cb                 	# Compile with “color bleeding” mode
make re                 	# Recompile from scratch without “color bleeding” mode
make test_mandatory     	# Compile project without “color bleeding” mode and run the mandatory test scene
make test_bonus         	# Compile project without “color bleeding” mode and run the bonus test scene
make clean              	# Remove object files
make fclean             	# Full cleanup
make clean_screenshots  	# Delete all screenshots from <./screenshots/>
make fclean_screenshots 	# Delete all screenshots from <./screenshots/> and the <./screenshots/> directory
```

<br>

## Usage

| Argument | Range | Default | Description |
|----------|-------|---------|-------------|
| `scene.rt` | - | Required | Scene file to load |
| `width` | 426 - 4096 | 426 | Window width in pixels |
| `height` | 240 - 2160 | 240 | Window height in pixels |
| `fps` | 24 - 60 | 24 | Maximum frames per second |

<br>

## Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move camera forward/left/back/right |
| `Space` / `Shift` | Move camera up/down |
| `Arrow Keys` | Rotate camera view |
| `Mouse` | Look around (when captured) |
| `Left Click` | Select object |
| `P` | Take high-resolution screenshot |
| `M` | Enter mouse capture mode |
| `ESC` | Exit program |

<br>

## Scene File Format (.rt)

Scene files use a simple text format to define cameras, lights, and objects:

```
# Comment line (lines starting with #)

# === Required Elements (one each) ===
A <ratio> <R,G,B>                              # Ambient light (2 args)
C <x,y,z> <nx,ny,nz> <fov>                     # Camera (3 args)

# === Optional Elements (multiple allowed) ===
L <x,y,z> <brightness> [R,G,B]                 # Point light (2-3 args)

# === Geometric Primitives ===
sp <x,y,z> <diameter> <R,G,B>                  # Sphere (3 args)
pl <x,y,z> <nx,ny,nz> <R,G,B>                  # Plane (3 args)
cy <x,y,z> <nx,ny,nz> <diameter> <h> <R,G,B>   # Cylinder (5 args)
co <x,y,z> <nx,ny,nz> <angle> <h> <R,G,B>      # Cone (5 args)
```

<br>

## Parameter Ranges

| Parameter | Range | Validation | Description |
|-----------|-------|------------|-------------|
| Ambient ratio | 0.0 - 1.0 | Strict | Intensity of ambient light |
| Light brightness | 0.0 - 1.0 | Strict | Point light intensity |
| Light color | 0 - 255 | Strict | RGB components (optional, defaults to white) |
| FOV | 0 - 180 | Strict | Camera field of view in degrees |
| RGB colors | 0 - 255 | Strict | Color components for all objects |
| Normal vectors | -1.0 - 1.0 | Strict | Direction vectors for planes |
| Position | Any float | No limit | 3D coordinates (x,y,z) |
| Orientation | Any float | No limit | Camera/axis direction (auto-normalized) |
| Diameter/Height | Any float | No limit | Object dimensions |
| Cone angle | Any float | No limit | Opening angle in degrees |

<br>

## Bonus Identifiers

| Identifier | Arguments | Description |
|------------|-----------|-------------|
| `plc` | 3 | Plane with checkerboard pattern |
| `spt` | 5 | Sphere with PPM texture (+ optional bump map) |

**Textured sphere syntax:**

```
spt <x,y,z> <diameter> <R,G,B> <texture.ppm> [bump_map.ppm]
```

<br>

## Basic Scene
```
# Ambient light (ratio 0.2, white)
A 0.2 255,255,255

# Camera at (0,2,10), looking at -Z, 60 FOV
C 0,2,10 0,0,-1 60

# Two colored lights
L -5,10,5 0.8 255,255,255
L 5,8,3 0.6 255,200,150

# Objects
sp 0,1,0 2 255,100,100           # Red sphere
pl 0,0,0 0,1,0 150,150,150       # Gray floor
cy -3,0,0 0,1,0 1 3 100,255,100  # Green cylinder
```

<br>

## Bonus Features Scene
```
A 0.1 255,255,255
C 0,8,18 0,-0.2,-0.95 70

# RGB colored lights
L -12,18,12 0.6 255,200,200
L 12,15,8 0.5 200,200,255
L 0,20,5 0.4 200,255,200

# Spheres
sp -5,2.5,0 5 220,50,50
sp 0,3.5,-5 4 50,220,50

# Cylinders
cy -3,0,7 0,1,0 1.5 6 200,100,200
cy 3,0,7 0,1,0 1.5 6 100,200,200

# Cone
co 0,0,3 0,1,0 22 4 255,150,50

# Checkerboard floor + wall
plc 0,0,0 0,1,0 180,180,180
pl 0,0,-12 0,0,1 140,160,180
```

<br>

</details>

<details>
<summary><strong>📁 Project Structure</strong></summary>

<br>

```
miniRT/
├── includes/                           # Header files
├── src/                                # Source files
├── linux-minilibx/                     # MiniLibX graphics library
├── scenes/                             # Scene files (.rt)
├── screenshots/                        # Generated screenshots
├── Makefile
└── README.md
```

### Header Files (includes/)

| File | Description |
|------|-------------|
| `minirt.h` | Main header: application state, initialization and cleanup |
| `camera.h` | Camera structure: position, direction, FOV, viewport vectors |
| `escene.h` | Scene structure: objects, lights, camera and ambient light |
| `objects.h` | Geometric primitives: sphere, cylinder, plane, cone definitions |
| `parser.h` | Public parser API for scene file loading |
| `parser_internal.h` | Internal parser: validation, error handling, memory management |
| `ray.h` | Ray structure and ray-tracing operations |
| `hit.h` | Intersection data: hit point, normal, color, material |
| `light.h` | Point light: position, brightness, color |
| `ambient_light.h` | Ambient light: ratio and color |
| `vector.h` | 3D vector operations: dot, cross, normalize, scale |
| `texture.h` | Texture loading and UV mapping |
| `image.h` | Image buffer for pixel manipulation |
| `input.h` | Input state: keyboard and mouse handling |
| `messages.h` | Constants and error messages |

### Source Files (src/)

#### Main Entry Point
| File | Description |
|------|-------------|
| `minirt.c` | Program entry: argument parsing, initialization, main loop |

#### Camera Module (src/camera/)
| File | Description |
|------|-------------|
| `camera.c` | Camera constructor/destructor, viewport vector calculation |
| `camera_debug.c` | Debug functions for camera state output |
| `collisions.c` | Camera-object collision detection during movement |
| `events_drag.c` | Mouse drag handling for object manipulation |
| `events_key.c` | Keyboard input: movement, rotation, actions |
| `events_loop.c` | Main event loop processing |
| `events_mouse.c` | Mouse movement and click handling |
| `events_print.c` | Status messages for object selection |
| `events_select.c` | Object selection via raycast |
| `events_utils.c` | Utility functions: pixel-to-world conversion |
| `init.c` | Scene initialization from parsed data |
| `init_window.c` | MLX window and image buffer setup |

#### Scene Module (src/escene/)
| File | Description |
|------|-------------|
| `escene.c` | Scene construction from parsed primitives, validation |

#### Objects Module (src/objects/)
| File | Description |
|------|-------------|
| `cone.c` | Cone constructor: apex, axis, angle, height |
| `cone_hit.c` | Ray-cone intersection calculation |
| `cylinder.c` | Cylinder constructor: center, axis, diameter, height |
| `cylinder_hit.c` | Ray-cylinder intersection (body + caps) |
| `objects.c` | Object factory: type identification and construction |
| `objects_utils.c` | Utilities: get center, move object |
| `plane.c` | Plane constructor: point and normal |
| `shpere.c` | Sphere constructor: center, diameter, textures |
| `sphere_hit.c` | Ray-sphere intersection (quadratic formula) |

#### Parser Module (src/parser/)
| File | Description |
|------|-------------|
| `parser_scene.c` | Entry point: read .rt file, build primitive scene |
| `parser_assignment.c` | Assign parsed elements to scene structure |
| `parser_camera.c` | Parse camera: position, direction, FOV |
| `parser_light.c` | Parse lights: position, brightness, color |
| `parser_elements.c` | Parse ambient light element |
| `parser_objects.c` | Object parser dispatcher |
| `parser_obj_sphere.c` | Parse sphere: center, diameter, color |
| `parser_obj_plane.c` | Parse plane: point, normal, color |
| `parser_obj_cyl.c` | Parse cylinder/cone: position, axis, dimensions |
| `parser_general.c` | Generic parser for element lists |
| `parser_getlist.c` | Get specific element lists from scene |
| `parser_file.c` | File path handling and extension validation |
| `parser_validators.c` | Value validation: ranges, empty checks |
| `parser_valid_args.c` | Argument count validation per element type |
| `parser_valid_floats.c` | Float parsing and range validation |
| `parser_errors.c` | Error list: create, add, print, free |
| `parser_destructors.c` | Memory cleanup: float lists, lights, cameras |
| `parser_destruct_primitives.c` | Destructors for sphere, plane, cylinder primitives |
| `parser_destruct_scene.c` | Scene destructor: free all parsed data |
| `parsing_debug.c` | Debug: print parsed scene structure |

#### Ray Module (src/ray/)
| File | Description |
|------|-------------|
| `ray.c` | Ray creation, evaluation, camera ray generation |

#### Hit Module (src/hit/)
| File | Description |
|------|-------------|
| `hit.c` | Find closest hit, handle textures and bump maps |

#### Light Module (src/light/)
| File | Description |
|------|-------------|
| `light.c` | Light constructor: position, brightness, color |
| `light_calc.c` | Illumination: diffuse, specular, shadows, reflections |

#### Ambient Light Module (src/ambient_light/)
| File | Description |
|------|-------------|
| `ambient_light.c` | Ambient light constructor and application |

#### Render Module (src/render/)
| File | Description |
|------|-------------|
| `render.c` | Low-resolution rendering loop |
| `render_high.c` | High-resolution rendering with anti-aliasing |
| `screenshot.c` | BMP screenshot capture with timestamp |

#### Texture Module (src/texture/)
| File | Description |
|------|-------------|
| `texture.c` | PPM texture loading and memory management |
| `texture_effects.c` | Effects: bump mapping, desaturation, brightness |
| `texture_sample.c` | Sample color from texture at UV coordinates |
| `texture_uv.c` | UV coordinate calculation for each object type |

#### Vector Module (src/vector/)
| File | Description |
|------|-------------|
| `vector.c` | Vector constructor from float lists |
| `vector_ops.c` | Operations: add, subtract, dot, cross, normalize, scale |
| `vector_utils.c` | Utilities: color conversion, distance, comparison |

#### Library (src/aux_libft/)
Custom implementation of standard C library functions including string manipulation, memory operations, linked lists, and I/O utilities.

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
- **Compiler**: cc with `-Wall -Wextra -Werror`
- **Graphics Library**: MiniLibX (X11-based)
- **Platform**: Linux with X11
- **Default Resolution**: 426x240 (configurable up to 4096x2160)
- **Screenshot Resolution**: 4096x2160 (BMP format)
- **Color Depth**: 24-bit RGB
- **Target FPS**: 24 (configurable 24-60)

## Requirements

- Linux with X11
- GCC compiler
- Make
- X11 development libraries (`libx11-dev`, `libxext-dev`)

---

> [!NOTE]
> This project serves as a comprehensive introduction to ray-tracing and 3D computer graphics, demonstrating proficiency in mathematical visualization, geometric algorithms, and interactive graphics programming.
