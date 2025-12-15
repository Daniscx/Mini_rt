/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:31:11 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/15 20:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../linux-minilibx/mlx.h"
# include "../src/aux_libft/libft.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WIDTH 800
# define HEIGHT 600
# define WIN_TITLE "miniRT"
# define ESC_KEY 65307
# define EPSILON 0.0001

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}					t_ray;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}					t_obj_type;

typedef struct s_sphere
{
	t_vec3			center;
	double			diameter;
	t_vec3			color;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_vec3			color;
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			axis;
	double			diameter;
	double			height;
	t_vec3			color;
}					t_cylinder;

typedef struct s_object
{
	t_obj_type		type;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
}					t_object;

typedef struct s_hit
{
	bool			hit;
	double			t;
	t_vec3			point;
	t_vec3			normal;
	t_vec3			color;
}					t_hit;

typedef struct s_ambient
{
	double			ratio;
	t_vec3			color;
}					t_ambient;

typedef struct s_light
{
	t_vec3			position;
	double			brightness;
	t_vec3			color;
}					t_light;

typedef struct s_camera
{
	t_vec3			position;
	t_vec3			direction;
	t_vec3			right;
	t_vec3			up;
	double			fov;
	double			aspect_ratio;
}					t_camera;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			*lights;
	int				light_count;
	t_object		*objects;
	int				object_count;
}					t_scene;

typedef struct s_img
{
	void			*img_ptr;
	char			*pixels_ptr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_scene			scene;
}					t_minirt;

/* ============ PARSER PRIMITIVE (temporal) ============ */
typedef struct s_parse_primitive
{
	t_list			**object;
	t_list			**light;
	t_list			**al;
	t_list			**camera;
}					parse_primitive_t;

/* legacy scene_t para compatibilidad temporal */
typedef struct s_scene_legacy
{
	t_list			**object;
	t_list			**light;
	void			*al;
	void			*camera;
}					scene_t;

// =[ Error ]=============================================================== //

void				error_manager(char *error_message);

// =[ Init & CleanUp ]====================================================== //

void				minirt_init(t_minirt *rt);
void				minirt_cleanup(t_minirt *rt);

// =[ Events ]============================================================== //

int					close_handler(t_minirt *rt);
int					key_handler(int keycode, t_minirt *rt);

// =[ Camera ]============================================================== //

void				camera_init(t_camera *camera);
void				camera_move(t_camera *camera, t_vec3 offset);
void				camera_rotate(t_camera *camera, double yaw, double pitch);

// =[ Render ]============================================================== //

void				render_scene(t_minirt *rt);

// =[ Vector Operations ]=================================================== //

t_vec3				vec3_new(double x, double y, double z);
t_vec3				vec3_add(t_vec3 a, t_vec3 b);
t_vec3				vec3_sub(t_vec3 a, t_vec3 b);
t_vec3				vec3_scale(t_vec3 v, double scalar);
double				vec3_dot(t_vec3 a, t_vec3 b);
t_vec3				vec3_cross(t_vec3 a, t_vec3 b);
t_vec3				vec3_normalize(t_vec3 v);
double				vec3_length(t_vec3 v);
t_vec3				vec3_mult(t_vec3 a, t_vec3 b);
t_vec3				vec3_negate(t_vec3 v);
double				vec3_clamp(double value, double min, double max);
int					vec3_to_color(t_vec3 color);

// =[ Ray ]================================================================= //

t_ray				ray_new(t_vec3 origin, t_vec3 direction);
t_vec3				ray_at(t_ray ray, double t);
t_ray				ray_from_camera(t_camera *cam, int x, int y);

// =[ Intersections ]======================================================= //

t_hit				hit_new(void);
t_hit				intersect_sphere(t_ray ray, t_sphere *sp);
t_hit				intersect_plane(t_ray ray, t_plane *pl);
t_hit				intersect_cylinder(t_ray ray, t_cylinder *cy);
t_hit				find_closest_hit(t_ray ray, t_scene *scene);

// =[ Lighting ]============================================================ //

t_vec3				calculate_lighting(t_hit hit, t_scene *scene);
bool				is_in_shadow(t_vec3 point, t_vec3 light_dir, double light_dist, t_scene *scene);	// insert a line break to pass norminette - [ 42 ]

// =[ Scene Conversion ]==================================================== //

int					scene_load(t_scene *scene, char *filename);
int					scene_from_parse(t_scene *scene, parse_primitive_t *parsed);						// insert a line break to pass norminette - [ 42 ]
void				scene_free(t_scene *scene);

// =[ Parser (legacy) ]===================================================== //

scene_t				*scene_constructor(char *file);
void				scene_destructor(scene_t *scene);
parse_primitive_t	*parse_primiteve_contructor(char *file);
void				*parse_primiteve_destructor(parse_primitive_t *parse);
void				parser_file_name(char *file);
bool				if_betwen_values(float element_to_check, float minmun_value, float maximun_value);	// insert a line break to pass norminette - [ 42 ]
void				ambient_light_parser(void *actual_elem, void *list_to_add);
void				light_parser(void *actual_elem, void *list_to_add);
void				camera_parser(void *actual_elem, void *list_to_add);
t_list				**general_parser(t_list **list__to_track, void (*f)(void *, void *));				// insert a line break to pass norminette - [ 42 ]

// ========================================================================= //

#endif
