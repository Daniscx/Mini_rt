
# miniRT - Guia de Desarrollo

## Estado Actual: FUNCIONAL

El raytracer esta completamente implementado con las siguientes funcionalidades:

### Implementado
- [x] Parser directo de archivos .rt a estructuras tipadas
- [x] Generacion de rayos desde la camara
- [x] Interseccion rayo-esfera
- [x] Interseccion rayo-plano
- [x] Interseccion rayo-cilindro (cuerpo + tapas)
- [x] Iluminacion ambiental
- [x] Iluminacion difusa (Lambert)
- [x] Sombras duras
- [x] Movimiento de camara (WASD, flechas)

---

## Estructuras Principales

### Vector 3D
```c
typedef struct s_vec3
{
    double  x;
    double  y;
    double  z;
}   t_vec3;
```

### Rayo
```c
typedef struct s_ray
{
    t_vec3  origin;
    t_vec3  direction;
}   t_ray;
```

### Registro de Impacto
```c
typedef struct s_hit
{
    bool    hit;        // Si hubo impacto
    double  t;          // Distancia al impacto
    t_vec3  point;      // Punto de impacto
    t_vec3  normal;     // Normal en el punto
    t_vec3  color;      // Color del objeto [0-1]
}   t_hit;
```

### Objetos
```c
typedef enum e_obj_type { OBJ_SPHERE, OBJ_PLANE, OBJ_CYLINDER } t_obj_type;

typedef struct s_object
{
    t_obj_type  type;
    t_sphere    sphere;
    t_plane     plane;
    t_cylinder  cylinder;
}   t_object;
```

### Escena
```c
typedef struct s_scene
{
    t_ambient   ambient;
    t_camera    camera;
    t_light     *lights;
    int         light_count;
    t_object    *objects;
    int         object_count;
}   t_scene;
```

---

## Formato de Archivos .rt

```
A <ratio> <R,G,B>                      # Luz ambiental
C <x,y,z> <nx,ny,nz> <fov>            # Camara
L <x,y,z> <brightness> [R,G,B]        # Luz puntual
sp <x,y,z> <diameter> <R,G,B>         # Esfera
pl <x,y,z> <nx,ny,nz> <R,G,B>         # Plano
cy <x,y,z> <nx,ny,nz> <d> <h> <R,G,B> # Cilindro
```

### Ejemplo (scenes/test.rt)
```
A 0.2 255,255,255

C 0,0,5 0,0,-1 70

L 5,5,5 0.8 255,255,255

sp 0,0,-5 3 255,0,0
sp -3,0,-8 2 0,255,0
sp 3,0,-8 2 0,0,255

pl 0,-2,0 0,1,0 200,200,200
```

---

## Pipeline de Raytracing

### 1. Generacion de Rayos
```c
t_ray ray_from_camera(t_camera *cam, int x, int y)
{
    // Convierte coordenadas pixel a [-1, 1]
    u = (2.0 * (x + 0.5) / WIDTH - 1.0) * aspect_ratio * fov_scale;
    v = (1.0 - 2.0 * (y + 0.5) / HEIGHT) * fov_scale;

    // Direccion usando base ortonormal de la camara
    dir = cam->direction + u * cam->right + v * cam->up;
    return ray_new(cam->position, dir);
}
```

### 2. Intersecciones

**Esfera**: Ecuacion cuadratica `at² + bt + c = 0`
- a = D·D
- b = 2(O-C)·D
- c = (O-C)·(O-C) - r²

**Plano**: `t = (P0 - O)·N / (D·N)`

**Cilindro**:
- Cuerpo: Proyeccion perpendicular al eje
- Tapas: Interseccion con planos + verificacion de radio

### 3. Iluminacion

```
Color = Ambiente + Difuso

Ambiente = color * ambient.ratio * ambient.color
Difuso   = color * light.brightness * max(0, N·L) * !sombra
```

### 4. Sombras

```c
bool is_in_shadow(point, light_dir, light_dist, scene)
{
    // Rayo desde punto hacia luz (con offset para evitar auto-interseccion)
    shadow_ray = ray_new(point + light_dir * EPSILON, light_dir);
    hit = find_closest_hit(shadow_ray, scene);
    return (hit.hit && hit.t < light_dist);
}
```

---

## Controles

| Tecla | Accion |
|-------|--------|
| W | Mover camara adelante |
| S | Mover camara atras |
| A | Mover camara izquierda |
| D | Mover camara derecha |
| Space | Mover camara arriba |
| Shift | Mover camara abajo |
| ← → | Rotar camara (yaw) |
| ↑ ↓ | Rotar camara (pitch) |
| ESC | Salir |

---

## Posibles Mejoras (Bonus)

1. **Specular** (Phong): Añadir componente especular
   ```c
   R = reflect(-L, N);
   spec = pow(max(0, R·V), shininess) * light.brightness;
   ```

2. **Anti-aliasing**: Multi-sampling por pixel
   ```c
   for (i = 0; i < SAMPLES; i++)
       color += trace_ray(ray_jittered(x, y, i));
   color /= SAMPLES;
   ```

3. **Texturas**: Checkerboard, procedurales

4. **Multithreading**: Paralelizar filas de pixeles

---

## Comandos

```bash
make                        # Compilar
make re                     # Recompilar
./miniRT scenes/test.rt     # Ejecutar
```

---

## Referencias

- [Scratchapixel - Ray Tracing](https://www.scratchapixel.com/lessons/3d-basic-rendering/)
- [Ray-Sphere Intersection](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection)
- [Phong Reflection Model](https://en.wikipedia.org/wiki/Phong_reflection_model)

---
