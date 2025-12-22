/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/22 06:04:03 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static void	events_init(t_minirt *rt)
{
	mlx_hook(rt->win, KeyPress, KeyPressMask, key_press_handler, rt);
	mlx_hook(rt->win, KeyRelease, KeyReleaseMask, key_release_handler, rt);
	mlx_hook(rt->win, ButtonPress, ButtonPressMask, mouse_press_handler, rt);
	mlx_hook(rt->win, ButtonRelease, ButtonReleaseMask, mouse_release_handler,
		rt);
	mlx_hook(rt->win, MotionNotify, PointerMotionMask, mouse_move_handler, rt);
	mlx_hook(rt->win, Expose, ExposureMask, expose_handler, rt);
	mlx_hook(rt->win, DestroyNotify, StructureNotifyMask, close_handler, rt);
	mlx_loop_hook(rt->mlx, loop_handler, rt);
}

static void	malloc_error(t_minirt *rt)
{
	if (rt->mlx)
	{
		if (rt->img.img_ptr)
			mlx_destroy_image(rt->mlx, rt->img.img_ptr);
		if (rt->img_high.img_ptr)
			mlx_destroy_image(rt->mlx, rt->img_high.img_ptr);
		if (rt->win)
			mlx_destroy_window(rt->mlx, rt->win);
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
	error_manager("Memory allocation failed");
}

static int	create_image(t_minirt *rt, t_img *img, int w, int h)
{
	img->img_ptr = mlx_new_image(rt->mlx, w, h);
	if (!img->img_ptr)
		return (-1);
	img->pixels_ptr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	img->width = w;
	img->height = h;
	return (0);
}

void	minirt_init(t_minirt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		malloc_error(rt);
	rt->win = mlx_new_window(rt->mlx, rt->win_w, rt->win_h, WIN_TITLE);
	if (!rt->win)
		malloc_error(rt);
	center_window_on_screen(rt);
	if (create_image(rt, &rt->img, rt->win_w, rt->win_h) < 0)
		malloc_error(rt);
	if (create_image(rt, &rt->img_high, WIDTH_HIGH, HEIGHT_HIGH) < 0)
		malloc_error(rt);
	rt->high_res_mode = false;
	rt->needs_render = true;
	ft_bzero(&rt->input, sizeof(t_input));
	rt->input.selected_obj = NULL;
	events_init(rt);
}

void	minirt_cleanup(t_minirt *rt)
{
	if (rt->img.img_ptr)
		mlx_destroy_image(rt->mlx, rt->img.img_ptr);
	if (rt->img_high.img_ptr)
		mlx_destroy_image(rt->mlx, rt->img_high.img_ptr);
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
	//scene_free(&rt->scene);
}
