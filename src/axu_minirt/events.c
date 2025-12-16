/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 04:29:58 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Handles window close event (X button or window manager close).
** Frees all allocated resources and exits the program cleanly.
*/
int	close_handler(t_minirt *rt)
{
	minirt_cleanup(rt);
	exit(EXIT_SUCCESS);
}

/*
** Handles window expose event (window becomes visible after being hidden).
** Redraws the scene to ensure content is always visible.
*/
int	expose_handler(t_minirt *rt)
{
	if (rt->img.img_ptr)
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
	return (0);
}

/*
** Maps X11 keycodes to internal key indices for state tracking.
** Returns -1 if the key is not mapped.
*/
static int	get_key_index(int keycode)
{
	if (keycode == XK_w || keycode == XK_W)
		return (KEY_W);
	if (keycode == XK_a || keycode == XK_A)
		return (KEY_A);
	if (keycode == XK_s || keycode == XK_S)
		return (KEY_S);
	if (keycode == XK_d || keycode == XK_D)
		return (KEY_D);
	if (keycode == XK_space)
		return (KEY_SPACE);
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		return (KEY_SHIFT);
	if (keycode == XK_Left)
		return (KEY_LEFT);
	if (keycode == XK_Right)
		return (KEY_RIGHT);
	if (keycode == XK_Up)
		return (KEY_UP);
	if (keycode == XK_Down)
		return (KEY_DOWN);
	return (-1);
}

/*
** Handles key press events. Sets key state to true for movement keys.
** Special keys (ESC, P, M) are handled immediately.
*/
int	key_press_handler(int keycode, t_minirt *rt)
{
	int	key_idx;

	if (keycode == XK_Escape)
		close_handler(rt);
	else if (keycode == XK_p || keycode == XK_P)
	{
		rt->high_res_mode = true;
		render_high_res(rt);
	}
	else if (keycode == XK_m || keycode == XK_M)
		rt->input.mouse_captured = !rt->input.mouse_captured;
	else
	{
		key_idx = get_key_index(keycode);
		if (key_idx >= 0)
			rt->input.keys[key_idx] = true;
	}
	return (0);
}

/*
** Handles key release events. Sets key state to false for movement keys.
*/
int	key_release_handler(int keycode, t_minirt *rt)
{
	int	key_idx;

	key_idx = get_key_index(keycode);
	if (key_idx >= 0)
		rt->input.keys[key_idx] = false;
	return (0);
}

/*
** Handles mouse button press. Left click enables mouse capture for camera.
*/
int	mouse_press_handler(int button, int x, int y, t_minirt *rt)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		rt->input.mouse_captured = true;
		rt->input.last_mouse_x = x;
		rt->input.last_mouse_y = y;
	}
	else if (button == 3)
		rt->input.mouse_captured = false;
	return (0);
}

/*
** Handles mouse movement for camera rotation when mouse is captured.
** Calculates delta from last position and applies rotation.
*/
int	mouse_move_handler(int x, int y, t_minirt *rt)
{
	int		dx;
	int		dy;

	if (!rt->input.mouse_captured)
	{
		rt->input.last_mouse_x = x;
		rt->input.last_mouse_y = y;
		return (0);
	}
	dx = x - rt->input.last_mouse_x;
	dy = y - rt->input.last_mouse_y;
	rt->input.last_mouse_x = x;
	rt->input.last_mouse_y = y;
	if (dx != 0 || dy != 0)
	{
		mlx_mouse_hide(rt->mlx, rt->win);
		camera_rotate(&rt->scene.camera, dx * MOUSE_SENS, -dy * MOUSE_SENS);
		rt->needs_render = true;
	}
	return (0);
}

/*
** Processes movement input based on current key states.
** Handles simultaneous key presses correctly (e.g., W+A for diagonal).
*/
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

/*
** Processes rotation input based on current arrow key states.
*/
static void	process_rotation(t_minirt *rt)
{
	double	yaw;
	double	pitch;

	yaw = 0;
	pitch = 0;
	if (rt->input.keys[KEY_LEFT])
		yaw -= ROT_SPEED;
	if (rt->input.keys[KEY_RIGHT])
		yaw += ROT_SPEED;
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

/*
** Main loop handler called every frame by MLX.
** Processes input and renders when needed.
*/
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
