/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:30:37 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

static void	events_init(t_minirt *rt)
{
	mlx_hook(rt->win, KeyPress, KeyPressMask, key_handler, rt);
	mlx_hook(rt->win, DestroyNotify, StructureNotifyMask, close_handler, rt);
}

static void	malloc_error(t_minirt *rt)
{
	if (rt->mlx)
	{
		if (rt->win)
		{
			mlx_destroy_window(rt->mlx, rt->win);
		}
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
	error_manager("Error: Memory allocation failed");
}

void	minirt_init(t_minirt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		malloc_error(rt);
	rt->win = mlx_new_window(rt->mlx, WIDTH, HEIGHT, WIN_TITLE);
	if (!rt->win)
		malloc_error(rt);
	rt->img.img_ptr = mlx_new_image(rt->mlx, WIDTH, HEIGHT);
	if (!rt->img.img_ptr)
		malloc_error(rt);
	rt->img.pixels_ptr = mlx_get_data_addr(rt->img.img_ptr, &rt->img.bpp,
			&rt->img.line_len, &rt->img.endian);
	camera_init(&rt->camera);
	events_init(rt);
}

void	minirt_cleanup(t_minirt *rt)
{
	if (rt->img.img_ptr)
		mlx_destroy_image(rt->mlx, rt->img.img_ptr);
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
	if (rt->scene)
		escene_destructor(rt->scene);
}
