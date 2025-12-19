
# miniRT - Documentacion Tecnica Completa

---

## Tabla de Contenidos

1. [Fundamentos del Ray Tracing](#1-fundamentos-del-ray-tracing)
2. [Matematicas Vectoriales](#2-matematicas-vectoriales)
3. [Generacion de Rayos](#3-generacion-de-rayos)
4. [Intersecciones Rayo-Objeto](#4-intersecciones-rayo-objeto)
   - [4.1 Esfera](#41-interseccion-rayo-esfera)
   - [4.2 Plano](#42-interseccion-rayo-plano)
   - [4.3 Cilindro](#43-interseccion-rayo-cilindro)
   - [4.4 Cono](#44-interseccion-rayo-cono)
5. [Modelo de Iluminacion Phong](#5-modelo-de-iluminacion-phong)
6. [Sistema de Sombras](#6-sistema-de-sombras)
7. [Color Bleeding (Iluminacion Indirecta)](#7-color-bleeding-iluminacion-indirecta)
8. [Sistema de Texturas](#8-sistema-de-texturas)
9. [Bump Mapping](#9-bump-mapping)
10. [Sistema de Camara](#10-sistema-de-camara)
11. [Estructuras de Datos](#11-estructuras-de-datos)
12. [Arquitectura del Programa](#12-arquitectura-del-programa)
13. [Formato de Escenas (.rt)](#13-formato-de-escenas-rt)
14. [Constantes y Configuracion](#14-constantes-y-configuracion)
15. [Guia de Optimizacion](#15-guia-de-optimizacion)

---

## 1. Fundamentos del Ray Tracing

### Que es el Ray Tracing?

El ray tracing (trazado de rayos) es una tecnica de renderizado que simula el comportamiento fisico de la luz para generar imagenes fotorrealistas. A diferencia de la rasterizacion tradicional, el ray tracing traza rayos desde la camara a traves de cada pixel de la imagen hacia la escena 3D.

### Principio Fisico

En la realidad, la luz viaja desde las fuentes luminosas, rebota en los objetos y llega a nuestros ojos. El ray tracing invierte este proceso por eficiencia computacional: trazamos rayos desde el "ojo" (camara) hacia la escena.

### Algoritmo Basico

```
Para cada pixel (x, y) en la imagen:
    rayo = generar_rayo(camara, x, y)
    impacto = encontrar_interseccion_mas_cercana(rayo, escena)
    si impacto:
        color = calcular_iluminacion(impacto, escena)
    sino:
        color = color_fondo
    asignar_pixel(x, y, color)
```

### Implementacion en miniRT

El archivo `src/render/render.c` implementa este algoritmo:

```c
void render_scene(t_minirt *rt)
{
    int     x;
    int     y;
    t_ray   ray;

    rt->scene.camera.aspect_ratio = (double)rt->img.width / rt->img.height;
    y = -1;
    while (++y < rt->img.height)
    {
        x = -1;
        while (++x < rt->img.width)
        {
            ray = ray_from_camera(&rt->scene.camera, x, y, &rt->img);
            put_pixel(&rt->img, x, y, trace_ray(ray, &rt->scene));
        }
    }
    mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
}
```

### Definicion Matematica de un Rayo

Un rayo se define mediante:
- **O** (Origin): Punto de origen del rayo
- **D** (Direction): Vector direccion normalizado

La ecuacion parametrica del rayo es:

```
P(t) = O + t * D    donde t >= 0
```

Donde:
- `P(t)` es cualquier punto sobre el rayo
- `t` es el parametro que indica la distancia a lo largo del rayo
- `t = 0` corresponde al origen
- `t > 0` son puntos en la direccion del rayo

---

## 2. Matematicas Vectoriales

### Estructura del Vector 3D

```c
typedef struct s_vec3
{
    double  x;
    double  y;
    double  z;
}   t_vec3;
```

### Operaciones Vectoriales Fundamentales

#### 2.1 Creacion de Vector

```c
t_vec3 vec3_new(double x, double y, double z)
{
    t_vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}
```

#### 2.2 Suma de Vectores

**Formula matematica:**
```
A + B = (Ax + Bx, Ay + By, Az + Bz)
```

**Implementacion:**
```c
t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
    return (vec3_new(a.x + b.x, a.y + b.y, a.z + b.z));
}
```

**Uso:** Combinar desplazamientos, sumar contribuciones de luz.

#### 2.3 Resta de Vectores

**Formula matematica:**
```
A - B = (Ax - Bx, Ay - By, Az - Bz)
```

**Implementacion:**
```c
t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
    return (vec3_new(a.x - b.x, a.y - b.y, a.z - b.z));
}
```

**Uso:** Calcular vectores direccion entre dos puntos.

#### 2.4 Producto por Escalar

**Formula matematica:**
```
s * V = (s*Vx, s*Vy, s*Vz)
```

**Implementacion:**
```c
t_vec3 vec3_scale(t_vec3 v, double scalar)
{
    return (vec3_new(v.x * scalar, v.y * scalar, v.z * scalar));
}
```

**Uso:** Escalar intensidades de luz, mover puntos a lo largo de direcciones.

#### 2.5 Producto Escalar (Dot Product)

El producto escalar es fundamental para calculos de iluminacion y proyecciones.

**Formula matematica:**
```
A . B = Ax*Bx + Ay*By + Az*Bz = |A| * |B| * cos(theta)
```

**Propiedades importantes:**
- Si `A . B > 0`: Los vectores apuntan en direcciones similares (angulo < 90 grados)
- Si `A . B = 0`: Los vectores son perpendiculares
- Si `A . B < 0`: Los vectores apuntan en direcciones opuestas (angulo > 90 grados)

**Implementacion:**
```c
double vec3_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}
```

**Aplicaciones en miniRT:**
1. **Iluminacion difusa:** `max(0, N . L)` donde N es la normal y L la direccion a la luz
2. **Reflexion especular:** `(R . V)^n` para brillos
3. **Deteccion de caras visibles:** Si `N . V < 0`, la superficie mira hacia la camara
4. **Proyeccion de vectores:** Para calculos de cilindros y conos

#### 2.6 Producto Vectorial (Cross Product)

Produce un vector perpendicular a ambos vectores de entrada.

**Formula matematica:**
```
A x B = (Ay*Bz - Az*By, Az*Bx - Ax*Bz, Ax*By - Ay*Bx)
```

**Implementacion:**
```c
t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
    t_vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return (result);
}
```

**Aplicaciones en miniRT:**
1. **Calcular normales de superficies**
2. **Construir sistema de coordenadas de la camara** (vectores right y up)
3. **Calcular tangentes para bump mapping**

#### 2.7 Longitud del Vector

**Formula matematica:**
```
|V| = sqrt(Vx^2 + Vy^2 + Vz^2)
```

**Implementacion:**
```c
double vec3_length(t_vec3 v)
{
    return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
```

**Uso:** Calcular distancias, normalizar vectores.

#### 2.8 Normalizacion

Convierte cualquier vector en un vector unitario (longitud = 1).

**Formula matematica:**
```
V_normalizado = V / |V|
```

**Implementacion:**
```c
t_vec3 vec3_normalize(t_vec3 v)
{
    double len;

    len = vec3_length(v);
    if (len == 0.0)
        return (vec3_new(0.0, 0.0, 0.0));
    return (vec3_scale(v, 1.0 / len));
}
```

**Importancia:** Los vectores normalizados son esenciales para:
- Direcciones de rayos
- Normales de superficies
- Calculos de iluminacion consistentes

#### 2.9 Multiplicacion Componente a Componente

**Formula matematica:**
```
A * B = (Ax*Bx, Ay*By, Az*Bz)
```

**Implementacion:**
```c
t_vec3 vec3_mult(t_vec3 a, t_vec3 b)
{
    return (vec3_new(a.x * b.x, a.y * b.y, a.z * b.z));
}
```

**Uso:** Mezclar colores (color del objeto con color de la luz).

#### 2.10 Negacion

**Implementacion:**
```c
t_vec3 vec3_negate(t_vec3 v)
{
    return (vec3_new(-v.x, -v.y, -v.z));
}
```

**Uso:** Invertir direcciones, voltear normales.

#### 2.11 Conversion a Color

**Implementacion:**
```c
int vec3_to_color(t_vec3 color)
{
    int r, g, b;

    r = (int)(vec3_clamp(color.x, 0.0, 1.0) * 255.0);
    g = (int)(vec3_clamp(color.y, 0.0, 1.0) * 255.0);
    b = (int)(vec3_clamp(color.z, 0.0, 1.0) * 255.0);
    return ((r << 16) | (g << 8) | b);
}
```

**Nota:** Los colores internos se manejan en rango [0, 1] y se convierten a [0, 255] para la pantalla.

---

## 3. Generacion de Rayos

### Modelo de Camara

La camara define como vemos la escena. Se caracteriza por:

```c
typedef struct s_camera
{
    t_vec3  position;       // Posicion en el espacio
    t_vec3  direction;      // Vector "forward" (hacia donde mira)
    t_vec3  right;          // Vector "right" (perpendicular a direction)
    t_vec3  up;             // Vector "up" (perpendicular a direction y right)
    double  fov;            // Campo de vision en grados
    double  aspect_ratio;   // Relacion ancho/alto
    double  yaw;            // Rotacion horizontal (radianes)
    double  pitch;          // Rotacion vertical (radianes)
}   t_camera;
```

### Campo de Vision (FOV)

El FOV determina cuanto de la escena es visible. Un FOV mayor captura mas area pero introduce distorsion.

```
fov_scale = tan((fov * PI / 180) / 2)
```

- **FOV bajo (30-50 grados):** Efecto telefoto, poca distorsion
- **FOV medio (60-90 grados):** Vision natural humana
- **FOV alto (90-120 grados):** Gran angular, distorsion de barril

### Generacion del Rayo desde la Camara

**Archivo:** `src/ray/ray.c`

```c
t_ray ray_from_camera(t_camera *cam, int x, int y, t_img *img)
{
    double  u;
    double  v;
    double  fov_scale;
    t_vec3  dir;

    // 1. Calcular escala del FOV
    fov_scale = tan((cam->fov * M_PI / 180.0) / 2.0);

    // 2. Convertir coordenadas de pixel a NDC (Normalized Device Coordinates)
    // El +0.5 centra el rayo en el medio del pixel
    u = (2.0 * ((double)x + 0.5) / (double)img->width - 1.0) * cam->aspect_ratio;
    v = 1.0 - 2.0 * ((double)y + 0.5) / (double)img->height;

    // 3. Aplicar FOV
    u *= fov_scale;
    v *= fov_scale;

    // 4. Construir direccion del rayo
    dir = vec3_add(cam->direction,
            vec3_add(vec3_scale(cam->right, u), vec3_scale(cam->up, v)));

    return (ray_new(cam->position, dir));
}
```

**Explicacion paso a paso:**

1. **Conversion a NDC:** Las coordenadas de pixel (0 a width-1, 0 a height-1) se convierten a un rango [-1, 1].

2. **Aspect Ratio:** Se multiplica `u` por el aspect ratio para evitar distorsion horizontal.

3. **FOV Scale:** El factor de escala controla cuanto se "abre" el campo de vision.

4. **Construccion de direccion:** Se combina la direccion base de la camara con desplazamientos en los ejes right y up.

### Actualizacion de Vectores de la Camara

Cuando la camara rota, debemos recalcular sus vectores:

```c
void camera_rotate(t_camera *camera, double yaw_delta, double pitch_delta)
{
    double  cos_pitch, sin_pitch;
    double  cos_yaw, sin_yaw;
    double  max_pitch;

    max_pitch = 80.0 * M_PI / 180.0;  // Limitar a +-80 grados
    camera->yaw += yaw_delta;
    camera->pitch += pitch_delta;

    // Clamping del pitch para evitar gimbal lock
    if (camera->pitch > max_pitch)
        camera->pitch = max_pitch;
    if (camera->pitch < -max_pitch)
        camera->pitch = -max_pitch;

    // Calcular nueva direccion usando angulos de Euler
    cos_pitch = cos(camera->pitch);
    sin_pitch = sin(camera->pitch);
    cos_yaw = cos(camera->yaw);
    sin_yaw = sin(camera->yaw);

    camera->direction.x = cos_pitch * sin_yaw;
    camera->direction.y = sin_pitch;
    camera->direction.z = cos_pitch * cos_yaw;
    camera->direction = vec3_normalize(camera->direction);

    camera_update_vectors(camera);
}
```

**Matematica de la rotacion:**

El vector direccion se calcula usando coordenadas esfericas:
- `x = cos(pitch) * sin(yaw)`
- `y = sin(pitch)`
- `z = cos(pitch) * cos(yaw)`

---

## 4. Intersecciones Rayo-Objeto

El nucleo del ray tracing es determinar donde un rayo intersecta con los objetos de la escena. Para cada tipo de primitiva geometrica, derivamos una ecuacion matematica y la resolvemos para encontrar el parametro `t`.

### 4.1 Interseccion Rayo-Esfera

#### Definicion Geometrica

Una esfera se define por:
- **C** (Center): Centro de la esfera
- **r** (Radius): Radio de la esfera

Un punto P esta en la superficie de la esfera si:

```
|P - C|^2 = r^2
```

#### Derivacion Matematica

Sustituyendo la ecuacion del rayo `P(t) = O + tD`:

```
|O + tD - C|^2 = r^2
```

Sea **oc** = O - C (vector del centro al origen del rayo):

```
|oc + tD|^2 = r^2
(oc + tD) . (oc + tD) = r^2
|D|^2*t^2 + 2*(oc . D)*t + |oc|^2 - r^2 = 0
```

Esta es una ecuacion cuadratica de la forma `at^2 + bt + c = 0`:

```
a = D . D = 1 (si D esta normalizado)
b = 2 * (oc . D)
c = oc . oc - r^2

discriminante = b^2 - 4ac
```

**Interpretacion del discriminante:**
- `disc < 0`: No hay interseccion (el rayo no toca la esfera)
- `disc = 0`: Una interseccion (el rayo es tangente a la esfera)
- `disc > 0`: Dos intersecciones (el rayo atraviesa la esfera)

#### Implementacion

**Archivo:** `src/ray/intersect.c`

```c
t_hit intersect_sphere(t_ray ray, t_sphere *sp)
{
    t_hit   hit;
    t_vec3  oc;
    double  coef[3];
    double  disc;
    double  t;

    hit = hit_new();
    oc = vec3_sub(ray.origin, sp->center);

    // Coeficientes de la cuadratica
    coef[0] = vec3_dot(ray.direction, ray.direction);  // a
    coef[1] = 2.0 * vec3_dot(oc, ray.direction);       // b
    coef[2] = vec3_dot(oc, oc) - (sp->diameter / 2.0) * (sp->diameter / 2.0);  // c

    disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
    if (disc < 0)
        return (hit);  // No hay interseccion

    // Tomar la interseccion mas cercana (t menor)
    t = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
    if (t < EPSILON)  // Si esta detras o muy cerca
        t = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
    if (t < EPSILON)
        return (hit);

    hit.hit = true;
    hit.t = t;
    hit.point = ray_at(ray, t);
    hit.normal = vec3_normalize(vec3_sub(hit.point, sp->center));
    hit.color = sp->color;
    hit.texture = sp->texture;
    hit.bump_map = sp->bump_map;
    sphere_get_uv(hit.point, sp->center, &hit.u, &hit.v);

    return (hit);
}
```

#### Normal de la Esfera

La normal en cualquier punto de la esfera apunta desde el centro hacia el punto:

```
N = normalize(P - C)
```

#### Ejemplo Visual

```
         * * *
      *         *
    *     C       *     <- Centro de la esfera
   *       |       *
    *      |      *
      *    |    *        <- Radio r
         * * *
              \
               \
                O------>D    <- Rayo
```

---

### 4.2 Interseccion Rayo-Plano

#### Definicion Geometrica

Un plano infinito se define por:
- **P0** (Point): Un punto en el plano
- **N** (Normal): Vector normal al plano

Un punto P esta en el plano si:

```
(P - P0) . N = 0
```

Es decir, el vector desde P0 hasta P es perpendicular a la normal.

#### Derivacion Matematica

Sustituyendo la ecuacion del rayo:

```
(O + tD - P0) . N = 0
(O - P0) . N + t*(D . N) = 0
t = (P0 - O) . N / (D . N)
```

**Casos especiales:**
- Si `D . N = 0`: El rayo es paralelo al plano (no hay interseccion o infinitas)
- Si `t < 0`: La interseccion esta detras del origen del rayo

#### Implementacion

```c
t_hit intersect_plane(t_ray ray, t_plane *pl)
{
    t_hit   hit;
    double  denom;
    double  t;

    hit = hit_new();
    denom = vec3_dot(ray.direction, pl->normal);

    // Rayo paralelo al plano
    if (fabs(denom) < EPSILON)
        return (hit);

    t = vec3_dot(vec3_sub(pl->point, ray.origin), pl->normal) / denom;

    if (t < EPSILON)
        return (hit);

    hit.hit = true;
    hit.t = t;
    hit.point = ray_at(ray, t);
    hit.normal = pl->normal;

    // Voltear normal si golpeamos por detras
    if (denom > 0)
        hit.normal = vec3_negate(hit.normal);

    hit.color = pl->color;
    hit.specular = 0.3;  // Planos menos brillantes

    return (hit);
}
```

#### Ejemplo Visual

```
            N (Normal)
            ^
            |
------------+------------  <- Plano definido por P0 y N
           P0
          /
         /
        O------>D    <- Rayo
```

---

### 4.3 Interseccion Rayo-Cilindro

El cilindro es mas complejo porque tiene tres partes: el cuerpo curvo y dos tapas circulares.

#### Definicion Geometrica

Un cilindro se define por:
- **C** (Center): Centro de la base
- **A** (Axis): Vector eje normalizado (direccion del cilindro)
- **r** (Radius): Radio
- **h** (Height): Altura

#### Ecuacion del Cilindro Infinito

Para un cilindro a lo largo del eje A pasando por C:

```
|P - C - ((P - C) . A) * A|^2 = r^2
```

Esta ecuacion elimina la componente a lo largo del eje, dejando solo la distancia perpendicular.

#### Derivacion para el Cuerpo

Sea:
- `oc = O - C` (origen del rayo relativo al centro)
- `d_perp = D - (D . A) * A` (direccion perpendicular al eje)
- `oc_perp = oc - (oc . A) * A` (posicion perpendicular al eje)

La ecuacion cuadratica es:

```
a = d_perp . d_perp
b = 2 * (d_perp . oc_perp)
c = oc_perp . oc_perp - r^2
```

#### Verificacion de Altura

Despues de encontrar t, verificamos que el punto este dentro de los limites:

```
0 <= (P - C) . A <= h
```

#### Normal del Cuerpo

```
N = normalize(P - C - ((P - C) . A) * A)
```

#### Implementacion del Cuerpo

```c
static t_hit intersect_cylinder_body(t_ray ray, t_cylinder *cy)
{
    t_hit   hit;
    t_vec3  oc;
    t_vec3  d_perp;
    t_vec3  oc_perp;
    double  coef[3];
    double  disc;
    double  t;
    double  h;

    hit = hit_new();
    oc = vec3_sub(ray.origin, cy->center);

    // Proyectar perpendicular al eje
    d_perp = vec3_sub(ray.direction,
                      vec3_scale(cy->axis, vec3_dot(ray.direction, cy->axis)));
    oc_perp = vec3_sub(oc,
                       vec3_scale(cy->axis, vec3_dot(oc, cy->axis)));

    coef[0] = vec3_dot(d_perp, d_perp);
    coef[1] = 2.0 * vec3_dot(d_perp, oc_perp);
    coef[2] = vec3_dot(oc_perp, oc_perp)
              - (cy->diameter / 2.0) * (cy->diameter / 2.0);

    disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
    if (disc < 0)
        return (hit);

    t = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
    if (t < EPSILON)
        t = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
    if (t < EPSILON)
        return (hit);

    hit.point = ray_at(ray, t);
    h = vec3_dot(vec3_sub(hit.point, cy->center), cy->axis);

    // Verificar limites de altura
    if (h < 0 || h > cy->height)
        return (hit_new());

    hit.hit = true;
    hit.t = t;
    hit.normal = vec3_normalize(
        vec3_sub(vec3_sub(hit.point, cy->center),
                 vec3_scale(cy->axis, h)));
    hit.color = cy->color;

    return (hit);
}
```

#### Implementacion de las Tapas

Las tapas son discos: intersectamos con el plano y verificamos que este dentro del radio.

```c
static t_hit intersect_cylinder_caps(t_ray ray, t_cylinder *cy)
{
    t_hit   hit;
    t_hit   cap_hit;
    t_plane cap;
    double  dist;

    hit = hit_new();

    // Tapa inferior (en center)
    cap.normal = cy->axis;
    cap.point = cy->center;
    cap.color = cy->color;
    cap_hit = intersect_plane(ray, &cap);
    if (cap_hit.hit)
    {
        dist = vec3_length(vec3_sub(cap_hit.point, cy->center));
        if (dist <= cy->diameter / 2.0 && cap_hit.t < hit.t)
            hit = cap_hit;
    }

    // Tapa superior (en center + height * axis)
    cap.point = vec3_add(cy->center, vec3_scale(cy->axis, cy->height));
    cap_hit = intersect_plane(ray, &cap);
    if (cap_hit.hit)
    {
        dist = vec3_length(vec3_sub(cap_hit.point, cap.point));
        if (dist <= cy->diameter / 2.0 && cap_hit.t < hit.t)
            hit = cap_hit;
    }

    return (hit);
}
```

#### Ejemplo Visual

```
          _____
         /     \   <- Tapa superior
        |   A   |
        |   |   |  <- Altura h
        |   |   |
        |   C   |  <- Centro (base)
         \_____/   <- Tapa inferior

        <--r-->    <- Radio
```

---

### 4.4 Interseccion Rayo-Cono

El cono es la figura mas compleja del proyecto.

#### Definicion Geometrica

Un cono se define por:
- **apex**: Punto base del cono (vertice)
- **A** (Axis): Vector eje normalizado (desde apex hacia la punta)
- **theta** (Angle): Angulo de apertura
- **h** (Height): Altura

#### Ecuacion del Cono

Para un cono con punta en **T** (tip) y eje **A**:

```
(D . A)^2 - cos^2(theta) * (D . D) = 0   // Para la direccion
```

La ecuacion completa en forma cuadratica:

Sea `tip = apex + height * axis`:

```
oc = O - tip
dv = D . A
ocv = oc . A
cos2 = cos^2(angle)

a = dv^2 - cos2 * (D . D)
b = 2 * (dv * ocv - cos2 * (D . oc))
c = ocv^2 - cos2 * (oc . oc)
```

#### Restriccion de Altura

El punto debe estar entre la punta y la base:

```
-height <= (P - tip) . A <= 0
```

#### Normal del Cono

```
N = normalize(P - tip - ((P - tip) . A / cos^2) * A)
```

#### Implementacion

```c
static t_hit intersect_cone_body(t_ray ray, t_cone *co)
{
    t_vec3  tip;
    t_vec3  oc;
    double  cos2;
    double  coef[3];
    double  disc;
    double  t[2];
    double  dv, ocv;
    t_hit   hit1, hit2;

    // La punta esta en apex + height * axis
    tip = vec3_add(co->apex, vec3_scale(co->axis, co->height));

    // Calcular cos^2 del angulo
    cos2 = cos(co->angle * M_PI / 180.0);
    cos2 = cos2 * cos2;

    oc = vec3_sub(ray.origin, tip);
    dv = vec3_dot(ray.direction, co->axis);
    ocv = vec3_dot(oc, co->axis);

    // Coeficientes de la cuadratica
    coef[0] = dv * dv - cos2 * vec3_dot(ray.direction, ray.direction);
    coef[1] = 2.0 * (dv * ocv - cos2 * vec3_dot(ray.direction, oc));
    coef[2] = ocv * ocv - cos2 * vec3_dot(oc, oc);

    disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
    if (disc < 0)
        return (hit_new());

    t[0] = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
    t[1] = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);

    hit1 = cone_body_hit(ray, co, t[0], tip, cos2);
    hit2 = cone_body_hit(ray, co, t[1], tip, cos2);

    if (hit1.hit && (!hit2.hit || hit1.t < hit2.t))
        return (hit1);
    if (hit2.hit)
        return (hit2);
    return (hit_new());
}
```

#### Tapa del Cono

La base del cono es un disco circular en el apex:

```c
static t_hit intersect_cone_cap(t_ray ray, t_cone *co)
{
    t_hit   hit;
    t_hit   cap_hit;
    t_plane cap;
    double  dist;
    double  radius;

    hit = hit_new();

    // Radio de la base = altura * tan(angulo)
    radius = co->height * tan(co->angle * M_PI / 180.0);

    cap.normal = co->axis;
    cap.point = co->apex;
    cap.color = co->color;

    cap_hit = intersect_plane(ray, &cap);
    if (cap_hit.hit)
    {
        dist = vec3_length(vec3_sub(cap_hit.point, co->apex));
        if (dist <= radius)
            hit = cap_hit;
    }
    return (hit);
}
```

#### Ejemplo Visual

```
              *       <- Tip (punta)
             /|\
            / | \
           /  |  \    <- Angulo theta
          /   h   \
         /    |    \
        /_____|_____\  <- Base en apex
              apex
        <----r----->   <- Radio = h * tan(theta)
```

---

## 5. Modelo de Iluminacion Phong

El modelo Phong es un modelo empirico que simula como la luz interactua con las superficies. Tiene tres componentes:

### Formula General

```
I = Ia + Id + Is

I  = Iluminacion total
Ia = Componente ambiental
Id = Componente difusa
Is = Componente especular
```

### 5.1 Luz Ambiental

Simula la luz indirecta que llega a todas las superficies por igual.

**Formula:**
```
Ia = ka * La * Cobjeto

ka = coeficiente ambiental (0-1)
La = color de la luz ambiental
Cobjeto = color del objeto
```

**Implementacion:**
```c
ambient = vec3_mult(hit.color, scene->ambient.color);
ambient = vec3_scale(ambient, scene->ambient.ratio);
```

**Justificacion:** Sin luz ambiental, las areas en sombra serian completamente negras, lo cual no es realista.

### 5.2 Reflexion Difusa (Lambertiana)

Modela superficies mate que dispersan la luz en todas direcciones.

**Formula:**
```
Id = kd * Ld * max(0, N . L) * Cobjeto

kd = coeficiente difuso (brillo de la luz)
Ld = color de la luz
N  = normal de la superficie
L  = direccion hacia la luz (normalizada)
```

**Ley de Lambert:** La intensidad de luz reflejada es proporcional al coseno del angulo entre la normal y la direccion de la luz.

**Implementacion:**
```c
static t_vec3 calculate_diffuse(t_hit hit, t_light *light, t_scene *scene)
{
    t_vec3  light_dir;
    double  light_dist;
    double  diff;
    t_vec3  diffuse;

    light_dir = vec3_sub(light->position, hit.point);
    light_dist = vec3_length(light_dir);
    light_dir = vec3_normalize(light_dir);

    // Verificar sombras
    if (is_in_shadow(hit.point, light_dir, light_dist, scene))
        return (vec3_new(0, 0, 0));

    diff = vec3_dot(hit.normal, light_dir);
    if (diff < 0)
        diff = 0;

    diffuse = vec3_mult(hit.color, light->color);
    return (vec3_scale(diffuse, diff * light->brightness));
}
```

### 5.3 Reflexion Especular (Phong)

Modela los brillos que aparecen en superficies pulidas.

**Formula:**
```
Is = ks * Ls * max(0, R . V)^n

ks = coeficiente especular
Ls = color de la luz
R  = direccion de reflexion
V  = direccion hacia la camara
n  = exponente de brillo (mayor = brillo mas concentrado)
```

**Vector de Reflexion:**
```
R = 2 * (N . L) * N - L
```

**Implementacion:**
```c
static t_vec3 calculate_specular(t_hit hit, t_light *light, t_vec3 view_dir)
{
    t_vec3  light_dir;
    t_vec3  reflect_dir;
    double  spec;
    double  dot_nl;

    if (hit.specular <= 0)
        return (vec3_new(0, 0, 0));

    light_dir = vec3_normalize(vec3_sub(light->position, hit.point));
    dot_nl = vec3_dot(hit.normal, light_dir);

    if (dot_nl < 0)
        return (vec3_new(0, 0, 0));

    // Calcular reflexion: R = 2(N.L)N - L
    reflect_dir = vec3_sub(vec3_scale(hit.normal, 2.0 * dot_nl), light_dir);
    reflect_dir = vec3_normalize(reflect_dir);

    spec = vec3_dot(reflect_dir, view_dir);
    if (spec < 0)
        spec = 0;

    // Aplicar exponente y fuerza
    spec = pow(spec, SPECULAR_EXP) * SPECULAR_STRENGTH * light->brightness;

    return (vec3_scale(light->color, spec));
}
```

### Constantes de Iluminacion

```c
#define SPECULAR_EXP 32.0       // Exponente de brillo
#define SPECULAR_STRENGTH 0.5   // Intensidad del especular
```

- **SPECULAR_EXP:** Valores altos (64, 128) = brillos pequenos y concentrados. Valores bajos (8, 16) = brillos grandes y difusos.
- **SPECULAR_STRENGTH:** Controla la intensidad maxima del brillo.

### Funcion Principal de Iluminacion

```c
t_vec3 calculate_lighting(t_hit hit, t_scene *scene, t_vec3 view_dir)
{
    t_vec3  result;
    t_vec3  ambient;
    t_vec3  diffuse;
    t_vec3  specular;
    int     i;

    // Aplicar modificadores de superficie
    if (hit.bump_map)
        hit.normal = apply_bump_map(&hit);
    if (hit.texture)
        hit.color = apply_texture(&hit);
    if (hit.checkerboard)
        hit.color = apply_checkerboard(&hit);

    // Componente ambiental
    ambient = vec3_mult(hit.color, scene->ambient.color);
    ambient = vec3_scale(ambient, scene->ambient.ratio);
    result = ambient;

    // Para cada luz
    i = 0;
    while (i < scene->light_count)
    {
        diffuse = calculate_diffuse(hit, &scene->lights[i], scene);
        specular = calculate_specular(hit, &scene->lights[i], view_dir);
        result = vec3_add(result, diffuse);
        result = vec3_add(result, specular);
        i++;
    }

    // Color bleeding opcional
    if (COLOR_BLEEDING == 1)
        result = vec3_add(result,
                         vec3_mult(hit.color, calculate_color_bleeding(hit, scene)));

    return (result);
}
```

---

## 6. Sistema de Sombras

Las sombras anaden realismo al indicar que objetos bloquean la luz.

### Algoritmo de Shadow Ray

Para determinar si un punto esta en sombra:

1. Construir un rayo desde el punto hacia la luz
2. Verificar si algun objeto bloquea el camino
3. Si hay bloqueo antes de llegar a la luz, el punto esta en sombra

### Implementacion

```c
bool is_in_shadow(t_vec3 point, t_vec3 light_dir, double light_dist, t_scene *scene)
{
    t_ray   shadow_ray;
    t_hit   hit;

    // Offset del origen para evitar auto-interseccion
    shadow_ray.origin = vec3_add(point, vec3_scale(light_dir, EPSILON * 10));
    shadow_ray.direction = light_dir;

    hit = find_closest_hit(shadow_ray, scene);

    // En sombra si golpeamos algo antes de la luz
    if (hit.hit && hit.t < light_dist)
        return (true);
    return (false);
}
```

### Shadow Acne

Sin el offset EPSILON, el rayo de sombra podria intersectar con la misma superficie de donde se origina debido a errores de precision de punto flotante. Esto causa "shadow acne" - puntos oscuros aleatorios.

**Solucion:** Desplazar el origen del rayo ligeramente en direccion de la luz.

```c
shadow_ray.origin = vec3_add(point, vec3_scale(light_dir, EPSILON * 10));
```

---

## 7. Color Bleeding (Iluminacion Indirecta)

El color bleeding simula como la luz rebota entre superficies, transfiriendo color. Por ejemplo, una pared roja puede teñir de rojo los objetos cercanos.

### Teoria

En la realidad, la luz no solo viaja directamente desde las fuentes - rebota multiples veces. El color bleeding aproxima este comportamiento lanzando rayos secundarios.

### Activacion

El color bleeding se activa en tiempo de compilacion:

```c
#ifndef COLOR_BLEEDING
# define COLOR_BLEEDING 0
#endif
```

Compilar con `make cb` define `COLOR_BLEEDING=1`.

### Implementacion

```c
static t_vec3 calculate_color_bleeding(t_hit hit, t_scene *scene)
{
    t_vec3  result;
    t_vec3  sample_dir;
    t_ray   bounce_ray;
    t_hit   bounce_hit;
    int     samples;
    int     i;

    result = vec3_new(0, 0, 0);
    samples = 8;  // Numero de muestras
    i = 0;

    while (i < samples)
    {
        // Direccion pseudo-aleatoria alrededor de la normal
        sample_dir = vec3_normalize(vec3_add(hit.normal,
            vec3_new((i % 3) * 0.5 - 0.5,
                     ((i / 3) % 3) * 0.5 - 0.5,
                     ((i / 9) % 3) * 0.5 - 0.5)));

        // Rayo de rebote
        bounce_ray.origin = vec3_add(hit.point,
                                     vec3_scale(hit.normal, EPSILON * 10));
        bounce_ray.direction = sample_dir;

        // Ver que golpea
        bounce_hit = find_closest_hit(bounce_ray, scene);

        if (bounce_hit.hit)
            result = vec3_add(result, vec3_scale(bounce_hit.color, 0.2));

        i++;
    }

    return (vec3_scale(result, 1.0 / samples));
}
```

### Funcionamiento Detallado

1. **Generacion de direcciones:** Se generan 8 direcciones distribuidas alrededor de la normal usando un patron fijo (no aleatorio para consistencia).

2. **Lanzamiento de rayos secundarios:** Cada rayo se lanza desde el punto de impacto hacia las direcciones generadas.

3. **Acumulacion de color:** Si el rayo golpea otro objeto, se acumula una fraccion de su color.

4. **Promediado:** El resultado final se divide por el numero de muestras.

### Impacto en el Rendimiento

El color bleeding multiplica significativamente el tiempo de renderizado porque cada pixel puede requerir multiples intersecciones adicionales. Por eso es opcional.

### Ejemplo de Efecto

Sin color bleeding:
- Una esfera roja junto a una pared blanca se ve completamente separada

Con color bleeding:
- La pared adquiere un tinte rojo cerca de la esfera
- Se crea una sensacion de iluminacion global mas realista

---

## 8. Sistema de Texturas

Las texturas permiten aplicar imagenes a las superficies de los objetos, añadiendo detalle visual.

### Formato Soportado: PPM P6

El proyecto soporta texturas en formato PPM binario (P6):

```
P6
# Comentario opcional
<ancho> <alto>
<valor_maximo>
<datos_binarios_RGB>
```

**Ejemplo de header:**
```
P6
512 512
255
```

### Carga de Texturas

**Archivo:** `src/texture/texture.c`

```c
t_texture *texture_load_ppm(const char *filename)
{
    t_texture   *tex;
    int         fd;
    char        c;
    char        magic[3];
    int         max_val;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);

    // Verificar magic number "P6"
    if (read(fd, magic, 2) != 2 || magic[0] != 'P' || magic[1] != '6')
        return (close(fd), NULL);

    tex = malloc(sizeof(t_texture));
    if (!tex)
        return (close(fd), NULL);

    read(fd, &c, 1);
    tex->width = read_ppm_int(fd, &c);
    tex->height = read_ppm_int(fd, &c);
    max_val = read_ppm_int(fd, &c);
    tex->channels = 3;

    tex->data = malloc(tex->width * tex->height * 3);
    if (!tex->data || max_val != 255)
        return (free(tex->data), free(tex), close(fd), NULL);

    if (read(fd, tex->data, tex->width * tex->height * 3)
        != tex->width * tex->height * 3)
        return (free(tex->data), free(tex), close(fd), NULL);

    return (close(fd), tex);
}
```

### Coordenadas UV para Esferas

Para mapear una textura 2D sobre una esfera 3D, usamos coordenadas esfericas:

```c
void sphere_get_uv(t_vec3 point, t_vec3 center, double *u, double *v)
{
    t_vec3  local;
    double  theta;
    double  phi;

    local = vec3_normalize(vec3_sub(point, center));

    // theta: angulo horizontal (-PI a PI)
    theta = atan2(local.x, local.z);

    // phi: angulo vertical (-PI/2 a PI/2)
    phi = asin(local.y);

    // Convertir a rango [0, 1]
    *u = 1.0 - (theta + M_PI) / (2.0 * M_PI);
    *v = (phi + M_PI / 2.0) / M_PI;
}
```

**Explicacion matematica:**

1. **Normalizamos** el vector desde el centro de la esfera al punto de impacto.

2. **theta (azimut):** Angulo en el plano XZ, obtenido con `atan2(x, z)`.

3. **phi (elevacion):** Angulo desde el ecuador, obtenido con `asin(y)`.

4. **Conversion a UV:** Mapeamos los rangos angulares a [0, 1].

### Muestreo de Textura

```c
t_vec3 texture_sample(t_texture *tex, double u, double v)
{
    int             x;
    int             y;
    int             idx;
    unsigned char   *pixel;

    if (!tex || !tex->data)
        return (vec3_new(1, 0, 1));  // Magenta para error

    // Wrapping (repetir textura)
    u = u - floor(u);
    v = v - floor(v);

    x = (int)(u * tex->width);
    y = (int)(v * tex->height);

    if (x >= tex->width)
        x = tex->width - 1;
    if (y >= tex->height)
        y = tex->height - 1;

    idx = (y * tex->width + x) * tex->channels;
    pixel = &tex->data[idx];

    // Convertir de [0,255] a [0,1]
    return (vec3_new(pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0));
}
```

### Texturas Validas

| Propiedad | Requisito |
|-----------|-----------|
| Formato | PPM binario (P6) |
| Valor maximo | 255 |
| Canales | 3 (RGB) |
| Resolucion | Cualquiera (se recomienda potencia de 2) |
| Ubicacion | Relativa al ejecutable o ruta absoluta |

**Ejemplo de texturas incluidas:**
- `scenes/textures/earth.ppm` - Textura del planeta Tierra
- `scenes/textures/earth_bump.ppm` - Mapa de relieve para la Tierra

---

## 9. Bump Mapping

El bump mapping simula relieve en las superficies perturbando las normales segun un mapa de altura.

### Teoria

En lugar de modificar la geometria real (lo que seria costoso), modificamos las normales para que la iluminacion simule profundidad.

### Implementacion

```c
t_vec3 apply_bump_map(t_hit *hit)
{
    t_vec3  color_c;        // Color en el punto actual
    t_vec3  color_u;        // Color en u + delta
    t_vec3  color_v;        // Color en v + delta
    double  du;             // Derivada en U
    double  dv;             // Derivada en V
    t_vec3  tangent;        // Vector tangente
    t_vec3  bitangent;      // Vector bitangente
    t_vec3  perturbed;      // Normal perturbada
    double  delta;

    if (!hit->bump_map)
        return (hit->normal);

    delta = 0.001;

    // Muestrear el mapa de relieve en tres puntos
    color_c = texture_sample(hit->bump_map, hit->u, hit->v);
    color_u = texture_sample(hit->bump_map, hit->u + delta, hit->v);
    color_v = texture_sample(hit->bump_map, hit->u, hit->v + delta);

    // Calcular gradientes (aproximacion de derivada)
    du = (color_u.x + color_u.y + color_u.z) / 3.0
       - (color_c.x + color_c.y + color_c.z) / 3.0;
    dv = (color_v.x + color_v.y + color_v.z) / 3.0
       - (color_c.x + color_c.y + color_c.z) / 3.0;

    // Construir sistema de coordenadas tangente
    tangent = vec3_normalize(vec3_cross(hit->normal, vec3_new(0, 1, 0)));
    if (vec3_length(tangent) < EPSILON)
        tangent = vec3_normalize(vec3_cross(hit->normal, vec3_new(1, 0, 0)));
    bitangent = vec3_cross(hit->normal, tangent);

    // Perturbar la normal
    perturbed = vec3_add(hit->normal,
                         vec3_scale(tangent, -du * BUMP_STRENGTH * 10.0));
    perturbed = vec3_add(perturbed,
                         vec3_scale(bitangent, -dv * BUMP_STRENGTH * 10.0));

    return (vec3_normalize(perturbed));
}
```

### Funcionamiento Paso a Paso

1. **Muestreo:** Se muestrea el mapa de relieve en el punto actual y en puntos vecinos.

2. **Gradiente:** Se calcula cuanto cambia la "altura" (luminosidad) en las direcciones U y V.

3. **Sistema tangente:** Se construyen vectores tangente y bitangente perpendiculares a la normal.

4. **Perturbacion:** La normal se desplaza en direccion del gradiente.

### Constante de Bump Mapping

```c
#define BUMP_STRENGTH 0.8
```

Valores mas altos producen relieve mas pronunciado.

---

## 10. Sistema de Camara

### Controles de Navegacion

| Tecla | Accion |
|-------|--------|
| W, A, S, D | Movimiento horizontal |
| Space | Subir |
| Shift | Bajar |
| Flechas | Rotacion |
| M | Captura de raton |
| P | Screenshot alta resolucion |
| ESC | Salir |

### Movimiento

El movimiento se calcula relativo a la orientacion de la camara:

```c
void camera_move(t_camera *camera, t_vec3 offset)
{
    camera->position = vec3_add(camera->position, offset);
}
```

**Ejemplo de movimiento adelante:**
```c
offset = vec3_scale(camera->direction, MOVE_SPEED);
camera_move(camera, offset);
```

**Ejemplo de movimiento lateral:**
```c
offset = vec3_scale(camera->right, MOVE_SPEED);
camera_move(camera, offset);
```

### Resolucion Dual

El proyecto usa dos resoluciones:

1. **Baja (426x240):** Para navegacion en tiempo real
2. **Alta (4096x2160):** Para screenshots

```c
#define WIDTH_LOW 426
#define HEIGHT_LOW 240
#define WIDTH_HIGH 4096
#define HEIGHT_HIGH 2160
```

---

## 11. Estructuras de Datos

### Estructura Principal

```c
typedef struct s_minirt
{
    void        *mlx;           // Contexto MiniLibX
    void        *win;           // Ventana
    int         win_w;          // Ancho de ventana
    int         win_h;          // Alto de ventana
    t_img       img;            // Imagen de baja resolucion
    t_img       img_high;       // Imagen de alta resolucion
    t_scene     scene;          // Datos de la escena
    t_input     input;          // Estado de entrada
    bool        high_res_mode;  // Modo de alta resolucion
    bool        needs_render;   // Bandera de re-render
}   t_minirt;
```

### Estructura de Escena

```c
typedef struct s_scene
{
    t_ambient   ambient;        // Luz ambiental
    t_camera    camera;         // Camara de vista
    t_light     *lights;        // Array de luces
    int         light_count;    // Numero de luces
    t_object    *objects;       // Array de objetos
    int         object_count;   // Numero de objetos
}   t_scene;
```

### Registro de Impacto

```c
typedef struct s_hit
{
    bool        hit;            // Hubo impacto?
    double      t;              // Distancia a lo largo del rayo
    t_vec3      point;          // Punto de impacto
    t_vec3      normal;         // Normal en el punto
    t_vec3      color;          // Color del objeto
    double      specular;       // Coeficiente especular
    int         checkerboard;   // Patron de ajedrez?
    double      u, v;           // Coordenadas de textura
    t_texture   *texture;       // Textura opcional
    t_texture   *bump_map;      // Bump map opcional
}   t_hit;
```

---

## 12. Arquitectura del Programa

### Flujo de Ejecucion

```
main()
    |
    +-> parser_file_name()     // Validar archivo
    |
    +-> scene_load()           // Cargar escena
    |
    +-> minirt_init()          // Inicializar MLX
    |
    +-> render_scene()         // Primer render
    |
    +-> mlx_loop()             // Bucle de eventos
            |
            +-> loop_handler()     // Procesar input
            |       |
            |       +-> camera_move/rotate()
            |       |
            |       +-> render_scene()  // Re-render
            |
            +-> key_press_handler()
            |
            +-> mouse_move_handler()
            |
            +-> close_handler()    // Limpieza
```

### Diagrama de Modulos

```
+------------------+
|     minirt.c     |  <- Entry point
+--------+---------+
         |
    +----+----+
    |         |
+---+---+ +---+----+
| parse | | scene  |
+-------+ +--------+
              |
    +---------+---------+
    |         |         |
+---+---+ +---+---+ +---+---+
|  ray  | | light | |render |
+-------+ +-------+ +-------+
    |
+---+---+
| math  |
+-------+
```

---

## 13. Formato de Escenas (.rt)

### Elementos Obligatorios

| Elemento | Sintaxis | Ejemplo |
|----------|----------|---------|
| Ambient | `A <ratio> <R,G,B>` | `A 0.2 255,255,255` |
| Camera | `C <x,y,z> <nx,ny,nz> <fov>` | `C 0,2,10 0,0,-1 60` |
| Light | `L <x,y,z> <brightness> [R,G,B]` | `L -5,10,5 0.8 255,255,255` |

### Primitivas

| Tipo | Sintaxis | Ejemplo |
|------|----------|---------|
| Sphere | `sp <x,y,z> <diameter> <R,G,B>` | `sp 0,1,0 2 255,100,100` |
| Plane | `pl <x,y,z> <nx,ny,nz> <R,G,B>` | `pl 0,0,0 0,1,0 150,150,150` |
| Cylinder | `cy <x,y,z> <nx,ny,nz> <diam> <h> <R,G,B>` | `cy -3,0,0 0,1,0 1 3 100,255,100` |
| Cone | `co <x,y,z> <nx,ny,nz> <angle> <h> <R,G,B>` | `co 0,0,5 0,1,0 30 2 255,200,0` |

### Primitivas Bonus

| Tipo | Sintaxis | Descripcion |
|------|----------|-------------|
| Plane Checker | `plc <x,y,z> <nx,ny,nz> <R,G,B>` | Plano con patron ajedrez |
| Sphere Textured | `spt <x,y,z> <diam> <R,G,B> <texture.ppm> [bump.ppm]` | Esfera con textura |

### Rangos de Parametros

| Parametro | Rango | Descripcion |
|-----------|-------|-------------|
| Ratio ambiental | 0.0 - 1.0 | Intensidad de luz ambiental |
| Brillo de luz | 0.0 - 1.0 | Intensidad de luz puntual |
| FOV | 0 - 180 | Campo de vision en grados |
| RGB | 0 - 255 | Componentes de color |
| Normales | -1.0 - 1.0 | Componentes de direccion |

### Ejemplo Completo

```
# Escena de demostración miniRT
# Luz ambiental suave
A 0.2 255,255,255

# Cámara posicionada atrás y arriba
C 0,5,-5 0,0,1 70

# Luces múltiples para sombras suaves
L -8,5,5 0.5 255,255,255
L 8,5,5 0.5 255,255,255

# Suelo con patrón de ajedrez
plc 0,0,0 0,1,0 100,100,100

# Esfera central roja
sp 0,2,10 4 255,50,50

# Cilindros como columnas
cy -5,0,8 0,1,0 1 4 200,200,200
cy 5,0,8 0,1,0 1 4 200,200,200

# Cono decorativo
co 0,0,15 0,1,0 25 3 255,200,0
```

---

## 14. Constantes y Configuracion

### Constantes Geometricas

```c
#define EPSILON 0.0001          // Tolerancia de punto flotante
#define M_PI 3.14159265358979   // Pi
```

### Constantes de Movimiento

```c
#define MOVE_SPEED 0.3          // Velocidad de movimiento
#define ROT_SPEED 0.05          // Velocidad de rotacion (teclado)
#define MOUSE_SENS 0.001        // Sensibilidad del raton
```

### Constantes de Iluminacion

```c
#define SPECULAR_EXP 32.0       // Exponente especular
#define SPECULAR_STRENGTH 0.5   // Fuerza del brillo
#define BUMP_STRENGTH 0.8       // Intensidad del bump mapping
```

### Constantes de Patron

```c
#define CHECKER_SCALE 2.0       // Tamano de cuadros del patron
```

### Resoluciones

```c
#define WIDTH_LOW 426           // Navegacion
#define HEIGHT_LOW 240

#define WIDTH_HIGH 4096         // Screenshots
#define HEIGHT_HIGH 2160
```

---

## 15. Guia de Optimizacion

### Optimizaciones Implementadas

1. **Direcciones Pre-normalizadas:** Los vectores de direccion se normalizan al crear el rayo, evitando recalculos.

2. **Early Exit en Sombras:** Los rayos de sombra terminan inmediatamente al encontrar cualquier interseccion.

3. **Epsilon para Precision:** Uso consistente de EPSILON para evitar errores de punto flotante.

4. **Buffer de Imagen:** Renderizado a buffer en memoria seguido de una sola operacion de display.

5. **Resolucion Dual:** Baja resolucion para interaccion, alta para calidad final.

### Flag de Optimizacion

El Makefile incluye `-O3` para optimizacion agresiva del compilador:

```makefile
CFLAGS = -Wall -Wextra -Werror -O3 ...
```

**Nota:** Durante la correccion, se recomienda remover `-O3` para detectar posibles errores que la optimizacion podria ocultar.

### Consejos de Rendimiento

1. **Escenas Complejas:** Reducir el numero de objetos o luces para navegacion fluida.

2. **Color Bleeding:** Desactivar para navegacion, activar solo para renders finales.

3. **Texturas:** Usar resoluciones de textura apropiadas (512x512 o 1024x1024 son suficientes).

4. **Screenshots:** Los screenshots de alta resolucion pueden tardar varios segundos - es normal.

---

## Apendice A: Diagrama de Clases (Estructuras)

```
t_minirt
├── mlx, win (MiniLibX)
├── t_img img, img_high
├── t_scene scene
│   ├── t_ambient ambient
│   ├── t_camera camera
│   ├── t_light[] lights
│   └── t_object[] objects
│       ├── t_sphere
│       ├── t_plane
│       ├── t_cylinder
│       └── t_cone
└── t_input input
```

---

## Apendice B: Referencias Matematicas Rapidas

### Ecuacion Cuadratica
```
ax² + bx + c = 0
x = (-b ± sqrt(b² - 4ac)) / 2a
```

### Ley de Snell (para reflexion)
```
R = D - 2(D·N)N
```

### Coordenadas Esfericas
```
x = r * cos(phi) * sin(theta)
y = r * sin(phi)
z = r * cos(phi) * cos(theta)
```

### Producto Escalar (propiedades)
```
A·B = |A||B|cos(θ)
A·A = |A|²
```

---

## Apendice C: Troubleshooting

### Problema: Shadow Acne
**Sintoma:** Puntos oscuros aleatorios en superficies iluminadas.
**Solucion:** Verificar que el offset EPSILON se aplica correctamente en rayos de sombra.

### Problema: Normales Invertidas
**Sintoma:** Objetos aparecen oscuros o con iluminacion incorrecta.
**Solucion:** Asegurar que las normales apuntan hacia afuera del objeto.

### Problema: Texturas Distorsionadas
**Sintoma:** La textura aparece estirada o comprimida.
**Solucion:** Verificar el calculo de coordenadas UV y el aspect ratio.

### Problema: Rendimiento Lento
**Sintoma:** La navegacion es lenta.
**Solucion:** Desactivar color bleeding, reducir numero de luces/objetos.

---

