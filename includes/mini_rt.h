/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:00:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 17:55:49 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H


#include "../libft/libft.h"
# include "../linux-minilibx/mlx.h"
#include "escene.h"
#include "image.h"
#include "input.h"

/* Main raytracer application structure */
typedef struct s_minirt
{
	void			*mlx;          /* MinilibX display connection */
	void			*win;          /* Window pointer */
	int				win_w;         /* Window width */
	int				win_h;         /* Window height */
	int				frame_rate;    /* Current FPS */
	t_img			img;           /* Low resolution image buffer */
	t_img			img_high;      /* High resolution image buffer */
	t_scene		*scene;        /* Scene data (objects, lights, camera) */
	t_input			input;         /* Input handling state */
	bool			high_res_mode; /* Flag for high resolution rendering */
	bool			needs_render;  /* Flag to trigger re-rendering */
	long			last_frame_time; /* Timestamp of last frame */
}					t_minirt;

# define TARGET_FPS 24

/* Error handling and setup */
void error_manager(char *error_message, bool exit_code); /* Print error message and exit */
void minirt_init(t_minirt *rt); /* Initialize raytracer application */
void minirt_cleanup(t_minirt *rt); /* Cleanup and free all resources */

/* Rendering functions */
void render_scene(t_minirt *rt); /* Render current scene to window */
void render_high_res(t_minirt *rt); /* Render high resolution output */

/* User interaction */
void handle_object_drag(t_minirt *rt, int x, int y); /* Handle dragging objects */
void print_grab_msg(t_object *obj, t_vec3 pos); /* Print object grab message */

/* File operations */
void generate_filename(char *filename); /* Generate unique filename for output */
int save_bmp(t_img *img, char *filename); /* Save rendered image as BMP */

#endif