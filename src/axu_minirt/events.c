/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:30:37 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

int	close_handler(t_minirt *rt)
{
	minirt_cleanup(rt);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keycode, t_minirt *rt)
{
	if (keycode == XK_Escape)
		close_handler(rt);
	else if (keycode == XK_w)
		camera_move(&rt->camera, vec3_scale(rt->camera.direction, 0.5));
	else if (keycode == XK_s)
		camera_move(&rt->camera, vec3_scale(rt->camera.direction, -0.5));
	else if (keycode == XK_a)
		camera_move(&rt->camera, vec3_scale(rt->camera.right, -0.5));
	else if (keycode == XK_d)
		camera_move(&rt->camera, vec3_scale(rt->camera.right, 0.5));
	else if (keycode == XK_space)
		camera_move(&rt->camera, vec3_scale(rt->camera.up, 0.5));
	else if (keycode == XK_Shift_L)
		camera_move(&rt->camera, vec3_scale(rt->camera.up, -0.5));
	else if (keycode == XK_Left)
		camera_rotate(&rt->camera, -0.1, 0.0);
	else if (keycode == XK_Right)
		camera_rotate(&rt->camera, 0.1, 0.0);
	else if (keycode == XK_Up)
		camera_rotate(&rt->camera, 0.0, 0.1);
	else if (keycode == XK_Down)
		camera_rotate(&rt->camera, 0.0, -0.1);
	render_scene(rt);
	return (0);
}
