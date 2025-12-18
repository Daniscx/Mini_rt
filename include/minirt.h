/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:01:26 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/18 12:13:03 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../linux-minilibx/mlx.h"
# include "../src/aux_libft/libft.h"

/* =[ Math Constants ]====================================================== */

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* =[ Defines ]============================================================= */

# define WIN_TITLE "miniRT"

# define WIDTH_LOW 426
# define HEIGHT_LOW 240

# define WIDTH_HIGH 4096
# define HEIGHT_HIGH 2160

# define EPSILON 0.0001
# define MOVE_SPEED 0.3
# define ROT_SPEED 0.05
# define MOUSE_SENS 0.001

# define CHECKER_SCALE 2.0
# define SPECULAR_EXP 32.0
# define SPECULAR_STRENGTH 0.5
# define BUMP_STRENGTH 0.8

# define SCREENSHOT_DIR "screenshots"

/* =[ Key State Indices ]=================================================== */

# define KEY_W 0
# define KEY_A 1
# define KEY_S 2
# define KEY_D 3
# define KEY_SPACE 4
# define KEY_SHIFT 5
# define KEY_LEFT 6
# define KEY_RIGHT 7
# define KEY_UP 8
# define KEY_DOWN 9
# define KEY_COUNT 10

/* =[ 3D Vector ]=========================================================== */

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

/* =[ Ray ]================================================================= */

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}					t_ray;

/* =[ Object Types ]======================================================== */

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE
}					t_obj_type;

/* =[ Texture ]============================================================= */

typedef struct s_texture
{
	unsigned char	*data;
	int				width;
	int				height;
	int				channels;
}					t_texture;

/* =[ Sphere ]============================================================== */

typedef struct s_sphere
{
	t_vec3			center;
	double			diameter;
	t_vec3			color;
	t_texture		*texture;
	t_texture		*bump_map;
}					t_sphere;

/* =[ Plane ]=============================================================== */

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_vec3			color;
}					t_plane;

/* =[ Cylinder ]============================================================ */

typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			axis;
	double			diameter;
	double			height;
	t_vec3			color;
}					t_cylinder;

/* =[ Cone ]================================================================ */

typedef struct s_cone
{
	t_vec3			apex;
	t_vec3			axis;
	double			angle;
	double			height;
	t_vec3			color;
}					t_cone;

/* =[ Generic Object ]====================================================== */

typedef struct s_object
{
	t_obj_type		type;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_cone			cone;
	int				checkerboard;
}					t_object;

/* =[ Hit Record ]========================================================== */

typedef struct s_hit
{
	bool			hit;
	double			t;
	t_vec3			point;
	t_vec3			normal;
	t_vec3			color;
	double			specular;
	int				checkerboard;
	double			u;
	double			v;
	t_texture		*texture;
	t_texture		*bump_map;
}					t_hit;

/* =[ Ambient Light ]======================================================= */

typedef struct s_ambient
{
	double			ratio;
	t_vec3			color;
}					t_ambient;

/* =[ Point Light ]========================================================= */

typedef struct s_light
{
	t_vec3			position;
	double			brightness;
	t_vec3			color;
}					t_light;

/* =[ Camera ]============================================================== */

typedef struct s_camera
{
	t_vec3			position;
	t_vec3			direction;
	t_vec3			right;
	t_vec3			up;
	double			fov;
	double			aspect_ratio;
	double			yaw;
	double			pitch;
}					t_camera;

/* =[ Scene ]=============================================================== */

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			*lights;
	int				light_count;
	t_object		*objects;
	int				object_count;
}					t_scene;

/* =[ MLX Image ]=========================================================== */

typedef struct s_img
{
	void			*img_ptr;
	char			*pixels_ptr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_img;

/* =[ Input State ]========================================================= */

typedef struct s_input
{
	bool			keys[KEY_COUNT];
	bool			mouse_captured;
	int				selected_obj;
	bool			dragging;
	t_vec3			drag_plane_point;
	t_vec3			drag_plane_normal;
}					t_input;

/* =[ Main Program State ]================================================== */

typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	int				win_w;
	int				win_h;
	t_img			img;
	t_img			img_high;
	t_scene			scene;
	t_input			input;
	bool			high_res_mode;
	bool			needs_render;
}					t_minirt;

/* =[ Legacy Parser Structures ]=( Change )================================= */

typedef struct s_parse_primitive
{
	t_list			**object;
	t_list			**light;
	t_list			**al;
	t_list			**camera;
}					t_parse_prim;

typedef struct s_scene_legacy
{
	t_list			**object;
	t_list			**light;
	void			*al;
	void			*camera;
}					t_scene_leg;

/* =[ Error Management ]==================================================== */

void				error_manager(char *error_message);

/* =[ Initialization & Cleanup ]============================================ */

void				minirt_init(t_minirt *rt);
void				minirt_cleanup(t_minirt *rt);
void				resize_window(t_minirt *rt, int width, int height);

/* =[ Event Handlers ]====================================================== */

int					close_handler(t_minirt *rt);
int					key_press_handler(int keycode, t_minirt *rt);
int					key_release_handler(int keycode, t_minirt *rt);
int					mouse_move_handler(int x, int y, t_minirt *rt);
int					mouse_press_handler(int btn, int x, int y, t_minirt *rt);
int					mouse_release_handler(int btn, int x, int y, t_minirt *rt);
int					expose_handler(t_minirt *rt);
int					loop_handler(t_minirt *rt);
void				warp_mouse_center(t_minirt *rt);

/* =[ Camera Operations ]=================================================== */

void				camera_init(t_camera *camera);
void				camera_move(t_camera *camera, t_vec3 offset);
void				camera_rotate(t_camera *camera, double yaw, double pitch);
void				camera_update_vectors(t_camera *camera);

/* =[ Rendering ]=========================================================== */

void				render_scene(t_minirt *rt);
void				render_high_res(t_minirt *rt);

/* =[ Vector Operations ]=================================================== */

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

/* =[ Ray Operations ]====================================================== */

t_ray				ray_new(t_vec3 origin, t_vec3 direction);
t_vec3				ray_at(t_ray ray, double t);
t_ray				ray_from_camera(t_camera *cam, int x, int y, t_img *img);

/* =[ Intersection Tests ]================================================== */

t_hit				hit_new(void);
t_hit				intersect_sphere(t_ray ray, t_sphere *sp);
t_hit				intersect_plane(t_ray ray, t_plane *pl);
t_hit				intersect_cylinder(t_ray ray, t_cylinder *cy);
t_hit				intersect_cone(t_ray ray, t_cone *co);
t_hit				find_closest_hit(t_ray ray, t_scene *scene);

/* =[ Lighting Calculations ]=============================================== */

t_vec3				calculate_lighting(t_hit hit, t_scene *scene, t_vec3 vdir);
bool				is_in_shadow(t_vec3 pt, t_vec3 ldir, double ldist, t_scene *scene);
t_vec3				apply_checkerboard(t_hit *hit);

/* =[ Scene Management ]==================================================== */

int					scene_load(t_scene *scene, char *filename, int route);
void				scene_free(t_scene *scene);

/* =[ Parser (Legacy) ]===================================================== */

t_scene_leg			*scene_constructor(char *file);
void				scene_destructor(t_scene_leg *scene);
t_parse_prim		*parse_primitive_constructor(char *file);
void				*parse_primitive_destructor(t_parse_prim *parse);
int					parser_file_name(char *file);
bool				if_between_values(float elem, float min, float max);
void				ambient_light_parser(void *elem, void *list);
void				light_parser(void *elem, void *list);
void				camera_parser(void *elem, void *list);
t_list				**general_parser(t_list **list, void (*f)(void *, void *));

/* =[ Texture Functions ]=================================================== */

t_texture			*texture_load_ppm(const char *filename);
void				texture_free(t_texture *tex);
t_vec3				texture_sample(t_texture *tex, double u, double v);
void				sphere_get_uv(t_vec3 point, t_vec3 center, double *u, double *v);
t_vec3				apply_bump_map(t_hit *hit);
t_vec3				apply_texture(t_hit *hit);

/* ========================================================================= */

#endif
