/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 10:43:23 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Handles window close event. Cleans up resources and exits the program.
*/
int	close_handler(t_minirt *rt)
{
	minirt_cleanup(rt);
	exit(EXIT_SUCCESS);
}

/*
** Handles window expose event. Redraws the current image to the window.
*/
int	expose_handler(t_minirt *rt)
{
	if (rt->high_res_mode && rt->img_high.img_ptr)
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img_high.img_ptr, 0, 0);
	else if (rt->img.img_ptr)
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
	return (0);
}

/*
** Maps X11 keycode to internal key index for tracking pressed keys.
** Returns -1 if the key is not a movement or rotation key.
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
** Handles key press events. Manages ESC to exit, P for resolution toggle,
** M for mouse capture mode, and movement keys for camera control.
*/
int	key_press_handler(int keycode, t_minirt *rt)
{
	int	key_idx;

	if (keycode == XK_Escape)
		close_handler(rt);
	else if (keycode == XK_p || keycode == XK_P)
	{
		if (rt->high_res_mode)
			render_low_res(rt);
		else
			render_high_res(rt);
	}
	else if ((keycode == XK_m || keycode == XK_M) && !rt->high_res_mode)
	{
		rt->input.mouse_captured = !rt->input.mouse_captured;
		if (rt->input.mouse_captured)
		{
			ft_bzero(rt->input.keys, sizeof(rt->input.keys));
			rt->input.mouse_x = WIDTH_LOW / 2;
			rt->input.mouse_y = HEIGHT_LOW / 2;
			rt->input.last_mouse_x = WIDTH_LOW / 2;
			rt->input.last_mouse_y = HEIGHT_LOW / 2;
			mlx_mouse_move(rt->mlx, rt->win, WIDTH_LOW / 2, HEIGHT_LOW / 2);
			mlx_mouse_hide(rt->mlx, rt->win);
		}
		else
		{
			ft_bzero(rt->input.keys, sizeof(rt->input.keys));
			rt->input.mouse_x = WIDTH_LOW / 2;
			rt->input.mouse_y = HEIGHT_LOW / 2;
			rt->input.last_mouse_x = WIDTH_LOW / 2;
			rt->input.last_mouse_y = HEIGHT_LOW / 2;
			mlx_mouse_move(rt->mlx, rt->win, WIDTH_LOW / 2, HEIGHT_LOW / 2);
			mlx_mouse_show(rt->mlx, rt->win);
		}
	}
	else if (!rt->high_res_mode)
	{
		key_idx = get_key_index(keycode);
		if (key_idx >= 0)
			rt->input.keys[key_idx] = true;
	}
	return (0);
}

/*
** Handles key release events. Updates the key state array to stop movement.
*/
int	key_release_handler(int keycode, t_minirt *rt)
{
	int	key_idx;

	if (rt->high_res_mode)
		return (0);
	key_idx = get_key_index(keycode);
	if (key_idx >= 0)
		rt->input.keys[key_idx] = false;
	return (0);
}

/*
** Handles mouse button press events. Currently unused but required by MLX.
*/
int	mouse_press_handler(int button, int x, int y, t_minirt *rt)
{
	(void)x;
	(void)y;
	(void)button;
	(void)rt;
	return (0);
}

/*
** Handles mouse movement for FPS-style camera rotation when captured.
** Ignores large deltas to prevent jumps after window resize or wrap-around.
*/
int	mouse_move_handler(int x, int y, t_minirt *rt)
{
	int		dx;
	int		dy;
	int		center_x;
	int		center_y;

	if (rt->high_res_mode || !rt->input.mouse_captured)
		return (0);
	center_x = WIDTH_LOW / 2;
	center_y = HEIGHT_LOW / 2;
	if (x < 0 || x >= WIDTH_LOW || y < 0 || y >= HEIGHT_LOW)
	{
		mlx_mouse_move(rt->mlx, rt->win, center_x, center_y);
		rt->input.last_mouse_x = center_x;
		rt->input.last_mouse_y = center_y;
		return (0);
	}
	dx = x - center_x;
	dy = y - center_y;
	if (dx == 0 && dy == 0)
		return (0);
	if (abs(dx) > 50 || abs(dy) > 50)
	{
		mlx_mouse_move(rt->mlx, rt->win, center_x, center_y);
		rt->input.last_mouse_x = center_x;
		rt->input.last_mouse_y = center_y;
		return (0);
	}
	camera_rotate(&rt->scene.camera, -dx * MOUSE_SENS, -dy * MOUSE_SENS);
	rt->needs_render = true;
	mlx_mouse_move(rt->mlx, rt->win, center_x, center_y);
	return (0);
}

/*
** Processes WASD and Space/Shift keys to move camera in 3D space.
** Movement is relative to camera orientation for intuitive FPS controls.
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
** Processes arrow keys for camera rotation (yaw and pitch).
** Provides keyboard-based camera look control as alternative to mouse.
*/
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

/*
** Main loop hook called by MLX. Processes input and triggers re-render.
** Disabled during high resolution mode to prevent interference.
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
