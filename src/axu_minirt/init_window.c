/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/19 22:21:02 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	warp_mouse_center(t_minirt *rt)
{
	int	cx;
	int	cy;

	cx = rt->img.width / 2;
	cy = rt->img.height / 2;
	mlx_mouse_move(rt->mlx, rt->win, cx, cy);
}

void	center_window_on_screen(t_minirt *rt)
{
	Display	*display;
	Window	window;
	int		screen_w;
	int		screen_h;

	display = ((t_xvar *)rt->mlx)->display;
	window = ((t_winlist *)rt->win)->window;
	mlx_get_screen_size(rt->mlx, &screen_w, &screen_h);
	XMoveWindow(display, window, (screen_w - rt->win_w) / 2, (screen_h - rt->win_h) / 2);
	XFlush(display);
}

void	resize_window(t_minirt *rt, int width, int height)
{
	Display	*display;

	display = ((t_xvar *)rt->mlx)->display;
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	rt->win = mlx_new_window(rt->mlx, width, height, WIN_TITLE);
	if (!rt->win)
		error_manager("Window creation failed");
	XSync(display, False);
}
