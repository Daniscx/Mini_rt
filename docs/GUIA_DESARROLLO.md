# Guía de Desarrollo - miniRT

## 🎯 ¿Qué se ha hecho hasta ahora?

### Parser Completo ✅
He integrado el parser completo de dmaestro en tu código. Ahora puedes parsear:
- **Ambient Light** (A): Luz ambiental
- **Camera** (C): Cámara con posición, dirección y FOV
- **Light** (L): Luces puntuales
- **Sphere** (sp): Esferas
- **Plane** (pl): Planos
- **Cylinder** (cy): Cilindros

### Estructuras de Datos ✅
He añadido las siguientes estructuras en `include/minirt.h`:
- `t_ambient_light`: Para la luz ambiental
- `t_light`: Para luces puntuales
- `t_sphere`: Para esferas
- `t_plane`: Para planos
- `t_cylinder`: Para cilindros

## 📋 Próximos Pasos (Lo que TÚ vas a programar)

### 1. Crear funciones de conversión (PRÓXIMO PASO INMEDIATO)

El parser actualmente devuelve **listas de floats** anidadas. Necesitas convertir esas listas a las estructuras específicas.

**Ubicación**: `src/scene/scene.c`

**Funciones que necesitas crear**:

```c
// Convierte la lista parseada de ambient light a estructura
t_ambient_light *convert_ambient_light(t_list **al_list);

// Convierte la lista parseada de camera a estructura t_camera
void convert_camera_data(t_list **camera_list, t_camera *camera);

// Convierte una lista parseada de light a estructura
t_light *convert_light(t_list **light_list);

// Convierte una lista parseada de sphere a estructura
t_sphere *convert_sphere(t_list **sphere_list);

// Convierte una lista parseada de plane a estructura
t_plane *convert_plane(t_list **plane_list);

// Convierte una lista parseada de cylinder a estructura
t_cylinder *convert_cylinder(t_list **cylinder_list);
```

**Ejemplo de cómo funciona una lista parseada**:

```
Ambient Light parseado:
Node1: float* -> 0.2 (ratio)
Node2: t_list** -> [float* 255, float* 255, float* 255] (RGB)

Camera parseada:
Node1: t_list** -> [float* x, float* y, float* z] (posición)
Node2: t_list** -> [float* nx, float* ny, float* nz] (dirección)
Node3: float* -> 70 (FOV)
```

**Pasos para implementar `convert_ambient_light`**:
1. Accede al primer nodo: `(*al_list)->content` → ratio (float*)
2. Accede al segundo nodo: `(*al_list)->next->content` → lista RGB
3. Crea `t_ambient_light`, asigna ratio
4. Convierte RGB de [0-255] a [0.0-1.0]: `color / 255.0`
5. Retorna la estructura

### 2. Actualizar `scene_constructor` para usar las conversiones

Modifica `src/scene/scene.c` para que después de parsear, convierta todo a estructuras:

```c
scene_t *scene_constructor(char *file)
{
    scene_t *scene;
    parse_primitive_t *parsed;

    parsed = parse_primiteve_contructor(file);
    if (!parsed)
        return (NULL);

    scene = malloc(sizeof(scene_t));
    if (!scene)
    {
        parse_primiteve_destructor(parsed);
        return (NULL);
    }

    // AQUÍ ES DONDE USARÁS TUS FUNCIONES DE CONVERSIÓN
    scene->al = convert_ambient_light(parsed->al);
    scene->camera = convert_camera_data(parsed->camera, &rt->camera);

    // Para lights y objects necesitarás iterar las listas
    // y convertir cada elemento individual
    scene->light = convert_lights_list(parsed->light);
    scene->object = convert_objects_list(parsed->object);

    free(parsed);
    return (scene);
}
```

### 3. Actualizar la estructura `scene_t`

Cambia los tipos en `scene_t` para usar estructuras específicas en vez de `void*`:

```c
typedef struct s_scene
{
    t_list          **object;      // Lista de t_sphere*, t_plane*, t_cylinder*
    t_list          **light;       // Lista de t_light*
    t_ambient_light *al;           // Ya no void*, sino t_ambient_light*
    t_camera        *camera;       // Puntero a t_camera
} scene_t;
```

### 4. Eliminar el gradiente y preparar el render real

**Ubicación**: `src/render/render.c`

Actualmente `render_scene()` solo dibuja un gradiente azul. Necesitas cambiarlo para:

1. **Por cada píxel de la pantalla**:
   - Generar un rayo desde la cámara hacia ese píxel
   - Verificar si el rayo intersecta algún objeto
   - Si hay intersección, calcular el color con iluminación
   - Si no hay intersección, usar color de fondo

**Estructura básica del nuevo render**:

```c
void render_scene(t_minirt *rt)
{
    int x, y;
    t_vec3 ray_direction;
    int color;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            // 1. Generar rayo para este píxel
            ray_direction = generate_ray(&rt->camera, x, y);

            // 2. Buscar intersección con objetos
            color = trace_ray(&rt->camera.position, &ray_direction, rt->scene);

            // 3. Dibujar el píxel
            put_pixel(&rt->img, x, y, color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
}
```

## 🔬 Partes Matemáticas/Técnicas (Yo las haré o te ayudaré)

Las siguientes son las partes donde necesitarás mi ayuda explícita:

### 1. Generación de rayos (`generate_ray`)
```c
// Calcula la dirección del rayo desde la cámara hacia el píxel (x,y)
t_vec3 generate_ray(t_camera *camera, int pixel_x, int pixel_y);
```

### 2. Intersecciones con objetos
```c
// Calcula si un rayo intersecta una esfera
bool intersect_sphere(t_vec3 *ray_origin, t_vec3 *ray_dir,
                      t_sphere *sphere, float *t);

// Calcula si un rayo intersecta un plano
bool intersect_plane(t_vec3 *ray_origin, t_vec3 *ray_dir,
                     t_plane *plane, float *t);

// Calcula si un rayo intersecta un cilindro
bool intersect_cylinder(t_vec3 *ray_origin, t_vec3 *ray_dir,
                        t_cylinder *cylinder, float *t);
```

### 3. Cálculo de iluminación (Phong shading)
```c
// Calcula el color final de un punto con iluminación
t_vec3 calculate_lighting(t_vec3 *point, t_vec3 *normal,
                          t_vec3 *view_dir, scene_t *scene,
                          t_vec3 *object_color);
```

### 4. Normalización de vectores normales
```c
// Normaliza el vector normal de un plano/cilindro después de parsear
void normalize_normals(scene_t *scene);
```

## 📝 Plan de Trabajo Sugerido

### Fase 1: Conversión de datos (TÚ)
1. Implementa `convert_ambient_light()`
2. Implementa `convert_camera_data()`
3. Implementa `convert_light()`
4. Implementa `convert_sphere()`
5. Implementa `convert_plane()`
6. Implementa `convert_cylinder()`
7. Actualiza `scene_constructor()` para usar estas funciones

### Fase 2: Matemáticas básicas (YO te ayudo)
1. Función para generar rayos
2. Función de intersección con esfera
3. Función de intersección con plano

### Fase 3: Render básico (TÚ + YO)
1. TÚ: Estructura del bucle de render
2. YO: Lógica de trazado de rayos
3. TÚ: Integración y testing

### Fase 4: Iluminación (YO te ayudo)
1. Luz ambiental
2. Luz difusa
3. Luz especular (opcional)

### Fase 5: Cilindros y optimización (TÚ + YO)
1. YO: Intersección con cilindros
2. TÚ: Integración
3. TÚ: Optimizaciones y pulido

## 🧪 Cómo Testear el Parser

Crea un archivo de prueba `scenes/test.rt`:

```
A 0.2 255,255,255

C -50.0,0,20 0,0,1 70

L -40.0,50.0,0.0 0.6 255,255,255

sp 0.0,0.0,-20.6 12.6 255,0,0
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
```

Compila y ejecuta:
```bash
make
./miniRT scenes/test.rt
```

Deberías ver que el parser procesa correctamente todos los elementos sin errores.

## 🔍 Debugging

Para ver qué está parseando:
1. Añade prints en `src/scene/scene.c` después de parsear
2. Imprime los valores de las listas antes de convertir
3. Verifica que los valores coincidan con el archivo .rt

## ❓ Cuándo Pedirme Ayuda

- ✅ Cuando llegues a las intersecciones de rayos
- ✅ Cuando necesites la generación de rayos
- ✅ Cuando implementes iluminación
- ✅ Para la normalización de vectores
- ✅ Para cualquier fórmula matemática
- ✅ Si tienes dudas sobre cómo estructurar algo

## 🚀 Empecemos

Tu primer objetivo es implementar `convert_ambient_light()` en `src/scene/scene.c`.

**Tip**: Mira el código del parser en `src/parse/parse.c` para entender cómo se construyen las listas. Luego, haz el proceso inverso para extraer los datos.

¡Suerte! 🎨
