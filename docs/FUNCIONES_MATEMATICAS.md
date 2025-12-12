
# Funciones Matemáticas - Para que Claude las implemente

Este documento lista las funciones matemáticas y técnicas que **yo (Claude) voy a implementar** cuando me las pidas. Son las partes más complejas del raytracer.

## 🎯 Generación de Rayos

### generate_ray()
```c
/*
** Genera un rayo desde la cámara hacia un píxel específico
** Parámetros:
**   - camera: cámara configurada con posición, dirección, FOV, etc.
**   - pixel_x, pixel_y: coordenadas del píxel en la pantalla
** Retorna:
**   - Vector dirección del rayo (normalizado)
** Matemática involucrada:
**   - Conversión de coordenadas de pantalla a coordenadas NDC
**   - Proyección usando FOV y aspect ratio
**   - Transformación usando la base ortonormal de la cámara
*/
t_vec3 generate_ray(t_camera *camera, int pixel_x, int pixel_y);
```

**Cuándo pedírmela**: Cuando vayas a implementar el bucle de render y necesites generar rayos para cada píxel.

---

## 🔍 Intersecciones con Objetos

### intersect_sphere()
```c
/*
** Calcula la intersección de un rayo con una esfera
** Parámetros:
**   - ray_origin: punto de origen del rayo (posición cámara)
**   - ray_dir: dirección del rayo (normalizado)
**   - sphere: esfera con la que testear intersección
**   - t: [OUTPUT] distancia desde ray_origin hasta el punto de intersección
** Retorna:
**   - true si hay intersección
**   - false si no hay intersección
** Matemática involucrada:
**   - Ecuación cuadrática del rayo-esfera
**   - Resolución de ax² + bx + c = 0
**   - Discriminante para determinar si hay solución
**   - Selección de la intersección más cercana (t mínimo positivo)
** Fórmula clave:
**   ||ray_origin + t*ray_dir - sphere_center||² = (radius)²
*/
bool intersect_sphere(t_vec3 *ray_origin, t_vec3 *ray_dir,
                      t_sphere *sphere, float *t);
```

**Cuándo pedírmela**: Cuando empieces a implementar el trace_ray() y necesites detectar si un rayo golpea una esfera.

---

### intersect_plane()
```c
/*
** Calcula la intersección de un rayo con un plano
** Parámetros:
**   - ray_origin: punto de origen del rayo
**   - ray_dir: dirección del rayo (normalizado)
**   - plane: plano con punto y normal
**   - t: [OUTPUT] distancia hasta la intersección
** Retorna:
**   - true si hay intersección
**   - false si el rayo es paralelo al plano o no intersecta
** Matemática involucrada:
**   - Ecuación del plano: (P - P0) · N = 0
**   - Ecuación del rayo: P = O + t*D
**   - Resolver: ((O + t*D) - P0) · N = 0
**   - t = ((P0 - O) · N) / (D · N)
** Casos especiales:
**   - Si D · N ≈ 0: rayo paralelo al plano (no intersección)
**   - Si t < 0: intersección detrás del origen (ignorar)
*/
bool intersect_plane(t_vec3 *ray_origin, t_vec3 *ray_dir,
                     t_plane *plane, float *t);
```

**Cuándo pedírmela**: Después de tener las esferas funcionando, para añadir soporte de planos.

---

### intersect_cylinder()
```c
/*
** Calcula la intersección de un rayo con un cilindro
** Parámetros:
**   - ray_origin: punto de origen del rayo
**   - ray_dir: dirección del rayo (normalizado)
**   - cylinder: cilindro con centro, eje, diámetro y altura
**   - t: [OUTPUT] distancia hasta la intersección
** Retorna:
**   - true si hay intersección (con el cuerpo o las tapas)
**   - false si no hay intersección
** Matemática involucrada:
**   - Intersección con cilindro infinito (cuadrática en espacio proyectado)
**   - Clipping por altura (verificar si está dentro de [0, height])
**   - Intersección con tapas circulares (planos + círculo)
**   - Selección del t mínimo entre cuerpo y tapas
** Casos:
**   1. Intersección con cuerpo cilíndrico
**   2. Intersección con tapa superior
**   3. Intersección con tapa inferior
** Esta es LA MÁS COMPLEJA - definitivamente pídeme ayuda aquí
*/
bool intersect_cylinder(t_vec3 *ray_origin, t_vec3 *ray_dir,
                        t_cylinder *cylinder, float *t);
```

**Cuándo pedírmela**: Después de tener esferas y planos funcionando. Esta es compleja, te la haré completa.

---

## 💡 Iluminación (Modelo de Phong)

### calculate_lighting()
```c
/*
** Calcula el color final de un punto con iluminación Phong
** Parámetros:
**   - point: punto de intersección en el espacio 3D
**   - normal: normal en el punto de intersección (normalizado)
**   - view_dir: dirección hacia la cámara (normalizado)
**   - scene: escena con luces y ambient light
**   - object_color: color del objeto (material)
** Retorna:
**   - Color final RGB [0.0, 1.0] con iluminación aplicada
** Componentes de iluminación:
**   1. Ambient: color_ambient = ambient_light.ratio * ambient_light.color * object_color
**   2. Difusa: color_diffuse = Σ(light.brightness * max(0, N·L) * light.color * object_color)
**   3. Especular (opcional): color_specular = Σ(light.brightness * max(0, R·V)^shininess)
**
** Fórmula completa:
**   final_color = ambient + diffuse + specular
**   Clampeado a [0.0, 1.0] para evitar overexposure
** Notas:
**   - N: normal en el punto
**   - L: dirección hacia la luz (normalizado)
**   - V: dirección hacia la cámara (view_dir)
**   - R: reflexión de L respecto a N
*/
t_vec3 calculate_lighting(t_vec3 *point, t_vec3 *normal, t_vec3 *view_dir,
                          scene_t *scene, t_vec3 *object_color);
```

**Cuándo pedírmela**: Cuando tengas intersecciones básicas funcionando y quieras añadir iluminación realista.

---

## 🎨 Funciones de Soporte

### get_normal_at_intersection()
```c
/*
** Calcula la normal en un punto de intersección según el tipo de objeto
** Parámetros:
**   - point: punto de intersección
**   - object: objeto intersectado (sphere, plane, cylinder)
**   - object_type: tipo de objeto (enum)
** Retorna:
**   - Vector normal en ese punto (normalizado)
** Cálculos por tipo:
**   - Sphere: normal = normalize(point - center)
**   - Plane: normal = plane.normal (ya está normalizado)
**   - Cylinder: depende si es cuerpo o tapa
*/
t_vec3 get_normal_at_intersection(t_vec3 *point, void *object, int object_type);
```

---

### trace_ray() - Función Principal de Raytracing
```c
/*
** Lanza un rayo y determina qué color debe tener
** Parámetros:
**   - ray_origin: origen del rayo (usualmente posición de cámara)
**   - ray_dir: dirección del rayo (normalizado)
**   - scene: escena con todos los objetos y luces
** Retorna:
**   - Color RGB [0-255] del píxel
** Algoritmo:
**   1. Buscar intersección más cercana con todos los objetos
**   2. Si no hay intersección: retornar color de fondo
**   3. Si hay intersección:
**      a. Calcular punto de intersección
**      b. Calcular normal en ese punto
**      c. Calcular iluminación
**      d. Convertir color [0.0-1.0] a [0-255]
**      e. Retornar color final
*/
int trace_ray(t_vec3 *ray_origin, t_vec3 *ray_dir, scene_t *scene);
```

**Cuándo pedírmela**: Cuando tengas `generate_ray()` e `intersect_sphere()` y quieras juntar todo.

---

## 🔧 Funciones Vectoriales Adicionales

Puede que necesites estas funciones vectoriales adicionales:

```c
// Refleja un vector respecto a una normal
t_vec3 vec3_reflect(t_vec3 incident, t_vec3 normal);

// Clampea un valor entre min y max
float clamp(float value, float min, float max);

// Convierte color [0.0-1.0] a [0-255]
int color_to_int(t_vec3 color);
```

---

## 📝 Orden Recomendado para Pedirme las Funciones

1. **generate_ray()** - Para poder generar rayos básicos
2. **intersect_sphere()** - La intersección más simple
3. **trace_ray()** - Para juntar todo y ver esferas renderizadas
4. **calculate_lighting()** - Para añadir luces y que se vea bonito
5. **intersect_plane()** - Para añadir planos
6. **intersect_cylinder()** - La más compleja, al final

---

## 🎯 Cómo Pedirme Ayuda

Cuando llegues al punto de necesitar alguna de estas funciones, simplemente di:

> "Claude, necesito la función `generate_ray()` para generar rayos desde la cámara hacia los píxeles"

Y yo te la implementaré completa con:
- ✅ Código funcional y comentado
- ✅ Explicación matemática
- ✅ Manejo de casos especiales
- ✅ Optimizaciones

---

## 💭 Notas Finales

- Estas funciones usan **matemática vectorial intensiva**
- Involucran **álgebra lineal** (productos punto, cruz, proyecciones)
- Requieren **geometría analítica** (ecuaciones de rayos, planos, superficies)
- Son **críticas para el rendimiento** (se ejecutan millones de veces)

Por eso es mejor que yo las implemente cuando las necesites. Tú concéntrate en la arquitectura y la lógica general del programa. 🚀
