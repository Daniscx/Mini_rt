/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:24 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

static t_vec3	get_movement_input(t_minirt *rt)
{
	t_vec3	move;

	move = vec3_new(0, 0, 0);
	if (rt->input.keys[KEY_W])
		move = vec3_add(move, rt->scene->camera->direction);
	if (rt->input.keys[KEY_S])
		move = vec3_sub(move, rt->scene->camera->direction);
	if (rt->input.keys[KEY_A])
		move = vec3_sub(move, rt->scene->camera->right);
	if (rt->input.keys[KEY_D])
		move = vec3_add(move, rt->scene->camera->right);
	if (rt->input.keys[KEY_SPACE])
		move = vec3_add(move, rt->scene->camera->up);
	if (rt->input.keys[KEY_SHIFT])
		move = vec3_sub(move, rt->scene->camera->up);
	return (move);
}

static void	process_movement(t_minirt *rt)
{
	t_vec3	move;
	t_vec3	new_pos;

	move = get_movement_input(rt);
	if (vec3_length(move) > EPSILON)
	{
		move = vec3_scale(vec3_normalize(move), MOVE_SPEED);
		new_pos = vec3_add(rt->scene->camera->position, move);
		if (!camera_collides(new_pos, rt->scene))
		{
			camera_move(rt->scene->camera, move);
			rt->needs_render = true;
		}
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
		camera_rotate(rt->scene->camera, yaw, pitch);
		rt->needs_render = true;
	}
}

int	loop_handler(t_minirt *rt)
{
	long	current_time;
	long	elapsed;

	if (rt->high_res_mode)
		return (0);
	current_time = get_time_us();
	elapsed = current_time - rt->last_frame_time;
	if (elapsed < (1000000 / rt->frame_rate))
		return (0);
	rt->last_frame_time = current_time;
	process_movement(rt);
	process_rotation(rt);
	if (rt->needs_render)
	{
		render_scene(rt);
		rt->needs_render = false;
	}
	return (0);
}
