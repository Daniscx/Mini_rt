/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/17 21:02:17 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_INTERNAL_H
# define MINIRT_INTERNAL_H

# include "minirt.h"

typedef struct s_xvar
{
	Display		*display;
	Window		root;
	int			screen;
}				t_xvar;

typedef struct s_winlist
{
	Window		window;
}				t_winlist;

/* Screenshot functions */
void	generate_filename(char *filename);
int		save_bmp(t_img *img, char *filename);

/* Key autorepeat detection */
int		is_autorepeat_release(t_minirt *rt, int keycode);

/* Object manipulation */
t_vec3	get_object_center(t_object *obj);
void	move_object(t_object *obj, t_vec3 new_center);

/* Mouse look */
void	handle_mouse_look(t_minirt *rt, int x, int y);
void	handle_object_drag(t_minirt *rt, int x, int y);

/* Window functions */
void	center_window_on_screen(t_minirt *rt);

/* Print functions */
void	print_grab_msg(t_object *obj, t_vec3 pos);
void	print_drop_msg(t_object *obj, t_vec3 pos);

#endif
