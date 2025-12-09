/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:31:11 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 22:11:59 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../minilibx-linux/mlx.h"
#  include "../src/aux_libft/libft.h"

# define WIDTH 800
# define HEIGHT 600
# define WIN_TITLE "miniRT"

# define ESC_KEY 65307

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_img
{
	void			*img_ptr;
	char			*pixels_ptr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_camera
{
	t_vec3			position;
	t_vec3			direction;
	t_vec3			right;
	t_vec3			up;
	double			fov;
	double			aspect_ratio;
}					t_camera;

typedef struct s_escene
{
	t_list			**object;
	t_list			**light;
	void			*al;
	void			*camera;
}					escene_t;

typedef struct s_parse_primitive
{
	t_list			**object;
	t_list			**light;
	t_list			**al;
	t_list			**camera;
}					parse_primitive_t;

typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_camera		camera;
	escene_t		*scene;
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

escene_t			*escene_constructor(char *file);
void				escene_destructor(escene_t *escene);

parse_primitive_t	*parse_primiteve_contructor(char *file);
void				*parse_primiteve_destructor(parse_primitive_t *parse);

void				parser_file_name(char *file);
bool				if_betwen_values(float element_to_check, float minmun_value, float maximun_value);
void				ambient_light_parser(void *actual_elem, void *list_to_add);
void				light_parser(void *actual_elem, void *list_to_add);
void				camera_parser(void *actual_elem, void *list_to_add);
t_list				**general_parser(t_list **list__to_track, void f(void *, void *));

#endif
