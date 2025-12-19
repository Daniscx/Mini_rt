/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/19 15:03:35 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	get_key_index(int kc)
{
	if (kc == XK_w || kc == XK_W)
		return (KEY_W);
	if (kc == XK_a || kc == XK_A)
		return (KEY_A);
	if (kc == XK_s || kc == XK_S)
		return (KEY_S);
	if (kc == XK_d || kc == XK_D)
		return (KEY_D);
	if (kc == XK_space)
		return (KEY_SPACE);
	if (kc == XK_Shift_L || kc == XK_Shift_R)
		return (KEY_SHIFT);
	if (kc == XK_Left)
		return (KEY_LEFT);
	if (kc == XK_Right)
		return (KEY_RIGHT);
	if (kc == XK_Up)
		return (KEY_UP);
	if (kc == XK_Down)
		return (KEY_DOWN);
	return (-1);
}

static void	toggle_mouse_mode(t_minirt *rt)
{
	rt->input.mouse_captured = !rt->input.mouse_captured;
	if (rt->input.mouse_captured)
	{
		ft_printf("\033[1;33m[MOUSE MODE]\033[0;0m Enabled - Move mouse to look around\n");
		mlx_mouse_hide(rt->mlx, rt->win);
		mlx_mouse_move(rt->mlx, rt->win,
			rt->img.width / 2, rt->img.height / 2);
	}
	else
	{
		ft_printf("\033[1;33m[MOUSE MODE]\033[0;0m Disabled\n\n");
		mlx_mouse_show(rt->mlx, rt->win);
	}
}

int	key_press_handler(int keycode, t_minirt *rt)
{
	int	key_idx;

	if (keycode == XK_Escape)
		close_handler(rt);
	else if (keycode == XK_p || keycode == XK_P)
		render_high_res(rt);
	else if ((keycode == XK_m || keycode == XK_M) && !rt->high_res_mode)
		toggle_mouse_mode(rt);
	else if (!rt->high_res_mode)
	{
		key_idx = get_key_index(keycode);
		if (key_idx >= 0)
			rt->input.keys[key_idx] = true;
	}
	return (0);
}

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
