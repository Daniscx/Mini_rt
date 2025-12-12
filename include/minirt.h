/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:31:11 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/10 02:27:40 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../linux-minilibx/mlx.h"
#  include "../src/aux_libft/libft.h"

# define WIDTH 800
# define HEIGHT 600
# define WIN_TITLE "miniRT"

# define ESC_KEY 65307

/*
** Vector 3D para representar puntos, direcciones y colores
** Campos:
**   - x, y, z: componentes del vector
** Usos:
**   - Posiciones en el espacio 3D
**   - Direcciones normalizadas (vectores unitarios)
**   - Colores RGB (normalizados 0.0-1.0)
*/
typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

/*
** Imagen de MinilibX
** Campos:
**   - img_ptr: puntero a la imagen de MLX
**   - pixels_ptr: puntero al array de píxeles (obtenido con mlx_get_data_addr)
**   - bpp: bits por píxel
**   - line_len: bytes por línea
**   - endian: 0 = little endian, 1 = big endian
** Uso:
**   - Renderizar píxel por píxel directamente en memoria
**   - Más rápido que mlx_pixel_put
*/
typedef struct s_img
{
	void			*img_ptr;
	char			*pixels_ptr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

/*
** Cámara del raytracer
** Campos:
**   - position: posición de la cámara en el espacio 3D
**   - direction: vector de dirección normalizado (hacia dónde mira)
**   - right: vector derecho (perpendicular a direction y up)
**   - up: vector arriba (perpendicular a direction y right)
**   - fov: field of view en grados [0, 180]
**   - aspect_ratio: relación ancho/alto (WIDTH/HEIGHT)
** Funcionamiento:
**   - Los vectores direction, right y up forman una base ortonormal
**   - Se usan para calcular rayos desde la cámara hacia cada píxel
** TODO: Inicializar desde los datos parseados del archivo .rt
*/
typedef struct s_camera
{
	t_vec3			position;
	t_vec3			direction;
	t_vec3			right;
	t_vec3			up;
	double			fov;
	double			aspect_ratio;
}					t_camera;

/*
** Luz ambiental de la escena
** Campos:
**   - ratio: intensidad de la luz ambiental [0.0, 1.0]
**   - color: color RGB normalizado [0.0, 1.0]
*/
typedef struct s_ambient_light
{
	float			ratio;
	t_vec3			color;
}					t_ambient_light;

/*
** Luz puntual de la escena
** Campos:
**   - position: posición de la luz en el espacio
**   - brightness: intensidad de la luz [0.0, 1.0]
**   - color: color RGB normalizado [0.0, 1.0]
*/
typedef struct s_light
{
	t_vec3			position;
	float			brightness;
	t_vec3			color;
}					t_light;

/*
** Esfera
** Campos:
**   - center: centro de la esfera
**   - diameter: diámetro de la esfera
**   - color: color RGB normalizado [0.0, 1.0]
*/
typedef struct s_sphere
{
	t_vec3			center;
	float			diameter;
	t_vec3			color;
}					t_sphere;

/*
** Plano
** Campos:
**   - point: punto del plano
**   - normal: vector normal al plano (normalizado)
**   - color: color RGB normalizado [0.0, 1.0]
*/
typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_vec3			color;
}					t_plane;

/*
** Cilindro
** Campos:
**   - center: centro del cilindro
**   - axis: vector dirección del eje del cilindro (normalizado)
**   - diameter: diámetro del cilindro
**   - height: altura del cilindro
**   - color: color RGB normalizado [0.0, 1.0]
*/
typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			axis;
	float			diameter;
	float			height;
	t_vec3			color;
}					t_cylinder;

/*
** Escena completa del raytracer
** Campos:
**   - object: lista de objetos (spheres, planes, cylinders)
**   - light: lista de luces puntuales
**   - al: ambient light (luz ambiental)
**   - camera: datos de la cámara parseados
** Estado actual:
**   - Estructura poblada por el parser
**   - Datos en formato de listas anidadas (float* dentro de t_list)
** TODO: Convertir estos datos a structs específicas:
**   - t_sphere, t_plane, t_cylinder
**   - t_light
**   - t_ambient_light
*/
typedef struct s_scene
{
	t_list			**object;
	t_list			**light;
	void			*al;
	void			*camera;
}					scene_t;

/*
** Estructura temporal del parser
** Campos:
**   - object: lista de objetos parseados (sp, pl, cy)
**   - light: lista de luces parseadas (L)
**   - al: ambient light parseada (A)
**   - camera: cámara parseada (C)
** Uso:
**   - Estructura intermedia durante el parseo
**   - Se transfiere a scene_t después de parsear
**   - Se destruye después de transferir los datos
** Formato de datos:
**   - Cada campo es una lista de listas de floats
**   - Ejemplo camera: [[x,y,z], [nx,ny,nz], fov]
*/
typedef struct s_parse_primitive
{
	t_list			**object;
	t_list			**light;
	t_list			**al;
	t_list			**camera;
}					parse_primitive_t;

/*
** Estructura principal del programa miniRT
** Campos:
**   - mlx: conexión con el servidor X (mlx_init)
**   - win: ventana de MLX (mlx_new_window)
**   - img: imagen donde se renderiza la escena
**   - camera: cámara del raytracer (ya procesada)
**   - scene: escena parseada del archivo .rt
** Ciclo de vida:
**   1. main: inicializa con ft_bzero
**   2. scene_constructor: parsea el archivo .rt
**   3. minirt_init: crea mlx, win, img y configura camera
**   4. render_scene: renderiza la escena en img
**   5. mlx_loop: loop de eventos
**   6. minirt_cleanup: libera toda la memoria
*/
typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_camera		camera;
	scene_t		*scene;
}					t_minirt;

void				error_manager(char *error_message);

void				minirt_init(t_minirt *rt);
void				minirt_cleanup(t_minirt *rt);

int					close_handler(t_minirt *rt);
int					key_handler(int keycode, t_minirt *rt);

void				camera_init(t_camera *camera);
void				camera_move(t_camera *camera, t_vec3 offset);
void				camera_rotate(t_camera *camera, double yaw, double pitch);

void				render_scene(t_minirt *rt);

t_vec3				vec3_new(double x, double y, double z);
t_vec3				vec3_add(t_vec3 a, t_vec3 b);
t_vec3				vec3_sub(t_vec3 a, t_vec3 b);
t_vec3				vec3_scale(t_vec3 v, double scalar);
double				vec3_dot(t_vec3 a, t_vec3 b);
t_vec3				vec3_cross(t_vec3 a, t_vec3 b);
t_vec3				vec3_normalize(t_vec3 v);
double				vec3_length(t_vec3 v);

scene_t				*scene_constructor(char *file);
void				scene_destructor(scene_t *scene);

parse_primitive_t	*parse_primiteve_contructor(char *file);
void				*parse_primiteve_destructor(parse_primitive_t *parse);

void				parser_file_name(char *file);
bool				if_betwen_values(float element_to_check, float minmun_value, float maximun_value);
void				ambient_light_parser(void *actual_elem, void *list_to_add);
void				light_parser(void *actual_elem, void *list_to_add);
void				camera_parser(void *actual_elem, void *list_to_add);
t_list				**general_parser(t_list **list__to_track, void (*f)(void *, void *));

#endif
