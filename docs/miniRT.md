# miniRT - Guia de Desarrollo

## Estado Actual

### Completado
- [x] Parser de archivos .rt (A, C, L, sp, pl, cy)
- [x] Validacion de formato y rangos
- [x] Operaciones vectoriales basicas (add, sub, scale, dot, cross, normalize, length)
- [x] Estructura MLX (ventana, imagen, eventos)
- [x] Movimiento de camara (WASD, flechas)

### Pendiente
- [ ] Convertir datos parseados a estructuras tipadas
- [ ] Generar rayos desde la camara
- [ ] Interseccion rayo-esfera
- [ ] Interseccion rayo-plano
- [ ] Interseccion rayo-cilindro
- [ ] Iluminacion ambiental
- [ ] Iluminacion difusa (Lambert)
- [ ] Sombras duras

---

## Fase 1: Conversion de Datos Parseados

El parser devuelve listas de floats. Hay que convertirlas a estructuras tipadas.

### Funciones a implementar en `src/scene/`

```c
// Convierte la lista parseada a t_ambient_light
t_ambient_light  parse_to_ambient(t_list **al_list);

// Convierte la lista parseada a t_camera (ya configurada)
void             parse_to_camera(t_list **cam_list, t_camera *cam);

// Convierte la lista de luces a array de t_light
t_light         *parse_to_lights(t_list **light_list, int *count);

// Convierte la lista de objetos a estructuras tipadas
t_object        *parse_to_objects(t_list **obj_list, int *count);
```

### Estructura generica de objeto

```c
typedef enum e_obj_type
{
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER
}   t_obj_type;

typedef struct s_object
{
    t_obj_type  type;
    union {
        t_sphere    sphere;
        t_plane     plane;
        t_cylinder  cylinder;
    };
}   t_object;
```

---

## Fase 2: Generacion de Rayos

### Estructura del rayo

```c
typedef struct s_ray
{
    t_vec3  origin;     // Origen del rayo (posicion camara)
    t_vec3  direction;  // Direccion normalizada
}   t_ray;
```

### Funcion para generar rayo por pixel

```c
t_ray   ray_from_camera(t_camera *cam, int x, int y)
{
    double  u;
    double  v;
    double  fov_scale;
    t_vec3  dir;

    // Convertir coordenadas pixel a [-1, 1]
    u = (2.0 * (x + 0.5) / WIDTH - 1.0) * cam->aspect_ratio;
    v = 1.0 - 2.0 * (y + 0.5) / HEIGHT;

    // Aplicar FOV
    fov_scale = tan((cam->fov * M_PI / 180.0) / 2.0);
    u *= fov_scale;
    v *= fov_scale;

    // Calcular direccion usando base ortonormal de la camara
    dir = vec3_add(cam->direction,
          vec3_add(vec3_scale(cam->right, u),
                   vec3_scale(cam->up, v)));

    return ((t_ray){cam->position, vec3_normalize(dir)});
}
```

---

## Fase 3: Intersecciones

### Estructura de impacto

```c
typedef struct s_hit
{
    double      t;          // Distancia al impacto
    t_vec3      point;      // Punto de impacto
    t_vec3      normal;     // Normal en el punto
    t_vec3      color;      // Color del objeto
    bool        hit;        // Si hubo impacto
}   t_hit;
```

### Interseccion Rayo-Esfera

```c
// Ecuacion: |P - C|^2 = r^2
// Sustituyendo P = O + t*D:
// |O + t*D - C|^2 = r^2
// t^2(D·D) + 2t(D·(O-C)) + (O-C)·(O-C) - r^2 = 0
// Resolvemos ecuacion cuadratica: at^2 + bt + c = 0

t_hit   intersect_sphere(t_ray ray, t_sphere *sp)
{
    t_hit   hit;
    t_vec3  oc;
    double  a, b, c, discriminant, t;

    hit.hit = false;
    oc = vec3_sub(ray.origin, sp->center);
    a = vec3_dot(ray.direction, ray.direction);
    b = 2.0 * vec3_dot(oc, ray.direction);
    c = vec3_dot(oc, oc) - (sp->diameter / 2.0) * (sp->diameter / 2.0);
    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return (hit);

    t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t < 0.001)
        t = (-b + sqrt(discriminant)) / (2.0 * a);
    if (t < 0.001)
        return (hit);

    hit.hit = true;
    hit.t = t;
    hit.point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
    hit.normal = vec3_normalize(vec3_sub(hit.point, sp->center));
    hit.color = sp->color;
    return (hit);
}
```

### Interseccion Rayo-Plano

```c
// Ecuacion del plano: (P - P0) · N = 0
// Sustituyendo P = O + t*D:
// (O + t*D - P0) · N = 0
// t = (P0 - O) · N / (D · N)

t_hit   intersect_plane(t_ray ray, t_plane *pl)
{
    t_hit   hit;
    double  denom, t;

    hit.hit = false;
    denom = vec3_dot(ray.direction, pl->normal);

    if (fabs(denom) < 0.0001)  // Rayo paralelo al plano
        return (hit);

    t = vec3_dot(vec3_sub(pl->point, ray.origin), pl->normal) / denom;
    if (t < 0.001)
        return (hit);

    hit.hit = true;
    hit.t = t;
    hit.point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
    hit.normal = pl->normal;
    if (denom > 0)  // Ajustar normal si estamos "dentro"
        hit.normal = vec3_scale(hit.normal, -1);
    hit.color = pl->color;
    return (hit);
}
```

### Interseccion Rayo-Cilindro (cuerpo lateral)

```c
// Cilindro infinito: |P - C - ((P-C)·A)A|^2 = r^2
// Con tapas: verificar altura

t_hit   intersect_cylinder(t_ray ray, t_cylinder *cy)
{
    // 1. Intersectar con cilindro infinito (cuadratica)
    // 2. Verificar que t este dentro de la altura
    // 3. Intersectar con tapas (dos planos)
    // 4. Retornar el t mas cercano valido

    // Ver implementacion completa en codigo
}
```

---

## Fase 4: Iluminacion

### Modelo de iluminacion

```
Color_final = Ambiente + Difuso

Ambiente = color_objeto * luz_ambiental.ratio * luz_ambiental.color
Difuso   = color_objeto * luz.brightness * max(0, N · L)

Donde:
  N = normal en el punto de impacto
  L = direccion hacia la luz (normalizada)
```

### Funcion de calculo de color

```c
t_vec3  calculate_lighting(t_hit hit, t_scene *scene)
{
    t_vec3  ambient;
    t_vec3  diffuse;
    t_vec3  light_dir;
    double  diff;

    // Componente ambiental
    ambient = vec3_scale(hit.color, scene->ambient.ratio);
    ambient = vec3_mult(ambient, scene->ambient.color);  // componente a componente

    // Componente difusa
    diffuse = vec3_new(0, 0, 0);
    light_dir = vec3_normalize(vec3_sub(scene->light.position, hit.point));

    // Verificar sombra antes de calcular difuso
    if (!is_in_shadow(hit.point, light_dir, scene))
    {
        diff = fmax(0.0, vec3_dot(hit.normal, light_dir));
        diffuse = vec3_scale(hit.color, diff * scene->light.brightness);
    }

    return (vec3_add(ambient, diffuse));
}
```

---

## Fase 5: Sombras

### Verificar si un punto esta en sombra

```c
bool    is_in_shadow(t_vec3 point, t_vec3 light_dir, t_scene *scene)
{
    t_ray   shadow_ray;
    t_hit   hit;
    double  light_dist;

    // Rayo desde el punto hacia la luz
    shadow_ray.origin = vec3_add(point, vec3_scale(light_dir, 0.001)); // Offset para evitar auto-interseccion
    shadow_ray.direction = light_dir;

    light_dist = vec3_length(vec3_sub(scene->light.position, point));

    // Verificar interseccion con todos los objetos
    hit = find_closest_hit(shadow_ray, scene);

    // Si hay objeto entre el punto y la luz -> sombra
    if (hit.hit && hit.t < light_dist)
        return (true);
    return (false);
}
```

---

## Fase 6: Loop de Renderizado

### Funcion principal de render

```c
void    render_scene(t_minirt *rt)
{
    int     x, y;
    t_ray   ray;
    t_hit   hit;
    t_vec3  color;
    int     pixel_color;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ray = ray_from_camera(&rt->camera, x, y);
            hit = find_closest_hit(ray, rt->scene);

            if (hit.hit)
                color = calculate_lighting(hit, rt->scene);
            else
                color = vec3_new(0, 0, 0);  // Fondo negro

            pixel_color = vec3_to_color(color);
            put_pixel(&rt->img, x, y, pixel_color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
}
```

---

## Funciones Auxiliares Necesarias

### En vec3 (añadir)

```c
// Multiplicacion componente a componente (para colores)
t_vec3  vec3_mult(t_vec3 a, t_vec3 b);

// Negar vector
t_vec3  vec3_negate(t_vec3 v);

// Reflejar vector respecto a normal
t_vec3  vec3_reflect(t_vec3 v, t_vec3 n);
```

### Conversion color

```c
// Convertir vec3 [0,1] a int 0xRRGGBB
int     vec3_to_color(t_vec3 color);

// Clamp valor entre 0 y 1
double  clamp(double value, double min, double max);
```

---

## Orden de Implementacion Recomendado

1. **Conversion de datos** - Pasar de listas a estructuras tipadas
2. **Generacion de rayos** - Implementar ray_from_camera
3. **Esfera basica** - Solo interseccion, color plano
4. **Luz ambiental** - Iluminacion minima
5. **Luz difusa** - Modelo Lambert
6. **Plano** - Interseccion y renderizado
7. **Sombras** - Shadow rays
8. **Cilindro** - Cuerpo + tapas
9. **Optimizaciones** - Si es necesario

---

## Archivos a Crear/Modificar

```
src/
├── ray/
│   ├── ray.c              # t_ray, ray_from_camera
│   └── intersect.c        # Intersecciones con objetos
├── render/
│   └── render.c           # Loop principal (ya existe, modificar)
├── light/
│   └── lighting.c         # Calculo de iluminacion y sombras
├── scene/
│   └── scene_convert.c    # Conversion de listas a structs
└── math/
    └── vec3_color.c       # Funciones de color
```

---

## Referencias Utiles

- **Ray-Sphere**: [Scratchapixel](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection)
- **Ray-Plane**: Ecuacion P·N = d
- **Ray-Cylinder**: Proyeccion en eje + verificacion altura
- **Phong Lighting**: Ambient + Diffuse (+ Specular en bonus)
