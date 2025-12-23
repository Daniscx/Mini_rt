/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:00:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 02:47:42 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "escene.h"
# include "input.h"
# include "image.h"

/* =[ Defines ]=( Frame Rate )============================================== */

// Target frames per second for render loop (24-60 recommended)
# define TARGET_FPS 24

/* =[ Main Program State ]================================================== */
// Core application state: MLX context, window, images, scene and input

typedef struct s_minirt
{
	void	*mlx;
	void	*win;
	int		win_w;
	int		win_h;
	int		frame_rate;
	t_img	img;
	t_img	img_high;
	t_scene	*scene;
	t_input	input;
	bool	high_res_mode;
	bool	needs_render;
	long	last_frame_time;
}	t_minirt;

/* =[ Error Management ]==================================================== */

void	error_manager(char *error_message, bool exit_code);

/* =[ Initialization & Cleanup ]============================================ */

void	minirt_init(t_minirt *rt);
void	minirt_cleanup(t_minirt *rt);

/* =[ Rendering ]=========================================================== */

void	render_scene(t_minirt *rt);
void	render_high_res(t_minirt *rt);

/* =[ Object Manipulation ]================================================= */

void	handle_object_drag(t_minirt *rt, int x, int y);
void	print_grab_msg(t_object *obj, t_vec3 pos);
void	print_drop_msg(t_object *obj, t_vec3 pos);

/* =[ Screenshot Functions ]================================================ */

void	generate_filename(char *filename);
int		save_bmp(t_img *img, char *filename);

#endif
