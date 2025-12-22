/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/21 17:49:07 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	handle_mouse_look(t_minirt *rt, int x, int y)
{
	int	cx;
	int	cy;
	int	dx;
	int	dy;

	cx = rt->img.width / 2;
	cy = rt->img.height / 2;
	dx = x - cx;
	dy = y - cy;
	if (ft_abs(dx) > 1 || ft_abs(dy) > 1)
	{
		camera_rotate(rt->scene->camera, -dx * MOUSE_SENS, -dy * MOUSE_SENS);
		rt->needs_render = true;
		mlx_mouse_move(rt->mlx, rt->win, cx, cy);
	}
}

int	mouse_move_handler(int x, int y, t_minirt *rt)
{
	if (rt->high_res_mode)
		return (0);
	if (!rt->input.mouse_captured)
	{
		if (rt->input.dragging)
			handle_object_drag(rt, x, y);
		return (0);
	}
	handle_mouse_look(rt, x, y);
	return (0);
}
