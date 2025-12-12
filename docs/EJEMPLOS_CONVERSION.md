# Ejemplos de Conversión de Listas a Estructuras

## 📚 Entendiendo la Estructura de las Listas Parseadas

Cuando el parser lee el archivo `.rt`, guarda los datos en **listas enlazadas anidadas** con floats. Aquí está cómo se ven:

### Ambient Light (A 0.2 255,255,255)
```
t_list **al
    |
    ├─> Node 1: content = float* (0.2)
    |
    └─> Node 2: content = t_list**
                    |
                    ├─> Node 1: content = float* (255.0)
                    ├─> Node 2: content = float* (255.0)
                    └─> Node 3: content = float* (255.0)
```

### Camera (C -50.0,0,20 0,0,1 70)
```
t_list **camera
    |
    ├─> Node 1: content = t_list**  (posición x,y,z)
    |               |
    |               ├─> float* (-50.0)
    |               ├─> float* (0.0)
    |               └─> float* (20.0)
    |
    ├─> Node 2: content = t_list**  (dirección nx,ny,nz)
    |               |
    |               ├─> float* (0.0)
    |               ├─> float* (0.0)
    |               └─> float* (1.0)
    |
    └─> Node 3: content = float* (70.0)
```

### Sphere (sp 0.0,0.0,-20.6 12.6 255,0,0)
```
t_list **sphere
    |
    ├─> Node 1: content = char* ("sp")
    |
    ├─> Node 2: content = t_list**  (centro x,y,z)
    |               |
    |               ├─> float* (0.0)
    |               ├─> float* (0.0)
    |               └─> float* (-20.6)
    |
    ├─> Node 3: content = float* (12.6)  (diámetro)
    |
    └─> Node 4: content = t_list**  (color r,g,b)
                    |
                    ├─> float* (255.0)
                    ├─> float* (0.0)
                    └─> float* (0.0)
```

## 🔧 Ejemplo Completo: convert_ambient_light()

```c
/*
** Convierte la lista parseada de ambient light a t_ambient_light
** Estructura de entrada:
**   Node1: float* -> ratio
**   Node2: t_list** -> [float* r, float* g, float* b]
*/
t_ambient_light *convert_ambient_light(t_list **al_list)
{
    t_ambient_light *al;
    t_list *rgb_list;
    t_list *node;
    float rgb[3];
    int i;

    if (!al_list || !*al_list)
        return (NULL);

    al = malloc(sizeof(t_ambient_light));
    if (!al)
        return (NULL);

    // Nodo 1: Ratio
    al->ratio = *(float *)((*al_list)->content);

    // Nodo 2: Lista RGB
    rgb_list = *(t_list **)((*al_list)->next->content);

    // Extraer los 3 valores RGB
    node = rgb_list;
    i = 0;
    while (node && i < 3)
    {
        rgb[i] = *(float *)(node->content);
        node = node->next;
        i++;
    }

    // Convertir de [0-255] a [0.0-1.0]
    al->color.x = rgb[0] / 255.0;
    al->color.y = rgb[1] / 255.0;
    al->color.z = rgb[2] / 255.0;

    return (al);
}
```

## 🔧 Ejemplo: convert_camera_data()

```c
/*
** Convierte los datos parseados de camera a t_camera
** Estructura de entrada:
**   Node1: t_list** -> [float* x, float* y, float* z] (posición)
**   Node2: t_list** -> [float* nx, float* ny, float* nz] (dirección)
**   Node3: float* -> fov
*/
void convert_camera_data(t_list **camera_list, t_camera *camera)
{
    t_list *xyz_list;
    t_list *node;
    float pos[3];
    float dir[3];
    int i;

    if (!camera_list || !*camera_list || !camera)
        return;

    // Nodo 1: Posición (x,y,z)
    xyz_list = *(t_list **)((*camera_list)->content);
    node = xyz_list;
    i = 0;
    while (node && i < 3)
    {
        pos[i] = *(float *)(node->content);
        node = node->next;
        i++;
    }
    camera->position = vec3_new(pos[0], pos[1], pos[2]);

    // Nodo 2: Dirección (nx,ny,nz)
    xyz_list = *(t_list **)((*camera_list)->next->content);
    node = xyz_list;
    i = 0;
    while (node && i < 3)
    {
        dir[i] = *(float *)(node->content);
        node = node->next;
        i++;
    }
    camera->direction = vec3_normalize(vec3_new(dir[0], dir[1], dir[2]));

    // Nodo 3: FOV
    camera->fov = *(float *)((*camera_list)->next->next->content);
    camera->aspect_ratio = (double)WIDTH / (double)HEIGHT;

    // Calcular vectores right y up (base ortonormal)
    // up temporal apunta hacia arriba en Y
    t_vec3 world_up = vec3_new(0, 1, 0);

    // right = direction × world_up
    camera->right = vec3_normalize(vec3_cross(camera->direction, world_up));

    // up = right × direction (para asegurar ortogonalidad)
    camera->up = vec3_normalize(vec3_cross(camera->right, camera->direction));
}
```

## 🔧 Ejemplo: convert_sphere()

```c
/*
** Convierte una lista parseada de sphere a t_sphere
** Estructura de entrada:
**   Node1: char* -> "sp"
**   Node2: t_list** -> [float* x, float* y, float* z] (centro)
**   Node3: float* -> diameter
**   Node4: t_list** -> [float* r, float* g, float* b] (color)
*/
t_sphere *convert_sphere(t_list **sphere_list)
{
    t_sphere *sphere;
    t_list *xyz_list;
    t_list *rgb_list;
    t_list *node;
    float center[3];
    float color[3];
    int i;

    if (!sphere_list || !*sphere_list)
        return (NULL);

    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        return (NULL);

    // Saltar nodo 1 (identificador "sp")
    // Nodo 2: Centro (x,y,z)
    xyz_list = *(t_list **)((*sphere_list)->next->content);
    node = xyz_list;
    i = 0;
    while (node && i < 3)
    {
        center[i] = *(float *)(node->content);
        node = node->next;
        i++;
    }
    sphere->center = vec3_new(center[0], center[1], center[2]);

    // Nodo 3: Diámetro
    sphere->diameter = *(float *)((*sphere_list)->next->next->content);

    // Nodo 4: Color RGB
    rgb_list = *(t_list **)((*sphere_list)->next->next->next->content);
    node = rgb_list;
    i = 0;
    while (node && i < 3)
    {
        color[i] = *(float *)(node->content);
        node = node->next;
        i++;
    }
    // Convertir de [0-255] a [0.0-1.0]
    sphere->color = vec3_new(color[0] / 255.0, color[1] / 255.0, color[2] / 255.0);

    return (sphere);
}
```

## 🔧 Ejemplo: convert_plane()

```c
/*
** Convierte una lista parseada de plane a t_plane
** Estructura de entrada:
**   Node1: char* -> "pl"
**   Node2: t_list** -> [float* x, float* y, float* z] (punto)
**   Node3: t_list** -> [float* nx, float* ny, float* nz] (normal)
**   Node4: t_list** -> [float* r, float* g, float* b] (color)
*/
t_plane *convert_plane(t_list **plane_list)
{
    t_plane *plane;
    t_list *xyz_list;
    t_list *rgb_list;
    t_list *node;
    float point[3];
    float normal[3];
    float color[3];
    int i;

    if (!plane_list || !*plane_list)
        return (NULL);

    plane = malloc(sizeof(t_plane));
    if (!plane)
        return (NULL);

    // Nodo 2: Punto (x,y,z)
    xyz_list = *(t_list **)((*plane_list)->next->content);
    node = xyz_list;
    i = 0;
    while (node && i < 3)
    {
        point[i] = *(float *)(node->content);
        node = node->next;
        i++;
    }
    plane->point = vec3_new(point[0], point[1], point[2]);

    // Nodo 3: Normal (nx,ny,nz)
    xyz_list = *(t_list **)((*plane_list)->next->next->content);
    node = xyz_list;
    i = 0;
    while (node && i < 3)
    {
        normal[i] = *(float *)(node->content);
        node = node->next;
        i++;
    }
    // IMPORTANTE: Normalizar el vector normal
    plane->normal = vec3_normalize(vec3_new(normal[0], normal[1], normal[2]));

    // Nodo 4: Color RGB
    rgb_list = *(t_list **)((*plane_list)->next->next->next->content);
    node = rgb_list;
    i = 0;
    while (node && i < 3)
    {
        color[i] = *(float *)(node->content);
        node = node->next;
        i++;
    }
    plane->color = vec3_new(color[0] / 255.0, color[1] / 255.0, color[2] / 255.0);

    return (plane);
}
```

## 🔧 Función Auxiliar: Extraer Vec3 de Lista

Para evitar repetir código, puedes crear una función auxiliar:

```c
/*
** Extrae un t_vec3 de una t_list** de 3 floats
** Parámetros:
**   - list: lista con exactamente 3 nodos de float*
**   - normalize: si true, normaliza el vector resultante
*/
static t_vec3 extract_vec3_from_list(t_list **list, bool normalize)
{
    t_list *node;
    float values[3];
    int i;

    if (!list || !*list)
        return (vec3_new(0, 0, 0));

    node = *list;
    i = 0;
    while (node && i < 3)
    {
        values[i] = *(float *)(node->content);
        node = node->next;
        i++;
    }

    if (normalize)
        return (vec3_normalize(vec3_new(values[0], values[1], values[2])));
    return (vec3_new(values[0], values[1], values[2]));
}
```

Con esto puedes simplificar:

```c
// En vez de copiar todo el código de extracción
plane->point = extract_vec3_from_list(
    (t_list **)((*plane_list)->next->content), false);

plane->normal = extract_vec3_from_list(
    (t_list **)((*plane_list)->next->next->content), true);
```

## 📝 Notas Importantes

1. **Navegación de listas**:
   - `(*lista)->content`: contenido del primer nodo
   - `(*lista)->next`: siguiente nodo
   - `(*lista)->next->next`: nodo después del siguiente

2. **Castings**:
   - `(float *)`: cuando el content es directamente un float*
   - `(t_list **)`: cuando el content es otra lista
   - `(char *)`: cuando el content es un string (identificadores)

3. **Conversión de colores**:
   - Parser guarda: [0-255]
   - Tus estructuras necesitan: [0.0-1.0]
   - Fórmula: `color_normalizado = color_parseado / 255.0`

4. **Normalización de vectores**:
   - SIEMPRE normaliza normales de planos/cilindros
   - SIEMPRE normaliza la dirección de la cámara
   - NO normalices posiciones o centros

## 🎯 Dónde Poner Estas Funciones

Crea un nuevo archivo: `src/scene/convert.c`

Y añade al header (`include/minirt.h`):
```c
// Conversión de listas parseadas a estructuras
t_ambient_light *convert_ambient_light(t_list **al_list);
void            convert_camera_data(t_list **camera_list, t_camera *camera);
t_light         *convert_light(t_list **light_list);
t_sphere        *convert_sphere(t_list **sphere_list);
t_plane         *convert_plane(t_list **plane_list);
t_cylinder      *convert_cylinder(t_list **cylinder_list);
```

No olvides añadir `src/scene/convert.c` al Makefile!
