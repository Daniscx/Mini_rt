/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/19 15:03:35 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	process_movement(t_minirt *rt)
{
	t_vec3	move;

	move = vec3_new(0, 0, 0);
	if (rt->input.keys[KEY_W])
		move = vec3_add(move, rt->scene.camera.direction);
	if (rt->input.keys[KEY_S])
		move = vec3_sub(move, rt->scene.camera.direction);
	if (rt->input.keys[KEY_A])
		move = vec3_sub(move, rt->scene.camera.right);
	if (rt->input.keys[KEY_D])
		move = vec3_add(move, rt->scene.camera.right);
	if (rt->input.keys[KEY_SPACE])
		move = vec3_add(move, rt->scene.camera.up);
	if (rt->input.keys[KEY_SHIFT])
		move = vec3_sub(move, rt->scene.camera.up);
	if (vec3_length(move) > EPSILON)
	{
		move = vec3_scale(vec3_normalize(move), MOVE_SPEED);
		camera_move(&rt->scene.camera, move);
		rt->needs_render = true;
	}
}

static void	process_rotation(t_minirt *rt)
{
	double	yaw;
	double	pitch;

	yaw = 0;
	pitch = 0;
	if (rt->input.keys[KEY_LEFT])
		yaw += ROT_SPEED;
	if (rt->input.keys[KEY_RIGHT])
		yaw -= ROT_SPEED;
	if (rt->input.keys[KEY_UP])
		pitch += ROT_SPEED;
	if (rt->input.keys[KEY_DOWN])
		pitch -= ROT_SPEED;
	if (yaw != 0 || pitch != 0)
	{
		camera_rotate(&rt->scene.camera, yaw, pitch);
		rt->needs_render = true;
	}
}

int	loop_handler(t_minirt *rt)
{
	if (rt->high_res_mode)
		return (0);
	process_movement(rt);
	process_rotation(rt);
	if (rt->needs_render)
	{
		render_scene(rt);
		rt->needs_render = false;
	}
	return (0);
}
