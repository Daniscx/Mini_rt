/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Registers all X11 event hooks for the window.
** Includes keyboard (press/release), mouse motion, expose, and close events.
*/
static void	events_init(t_minirt *rt)
{
	mlx_hook(rt->win, KeyPress, KeyPressMask, key_press_handler, rt);
	mlx_hook(rt->win, KeyRelease, KeyReleaseMask, key_release_handler, rt);
	mlx_hook(rt->win, ButtonPress, ButtonPressMask, mouse_press_handler, rt);
	mlx_hook(rt->win, MotionNotify, PointerMotionMask, mouse_move_handler, rt);
	mlx_hook(rt->win, Expose, ExposureMask, expose_handler, rt);
	mlx_hook(rt->win, DestroyNotify, StructureNotifyMask, close_handler, rt);
	mlx_loop_hook(rt->mlx, loop_handler, rt);
}

/*
** Handles memory allocation errors during initialization.
** Frees any already-allocated resources and exits with error message.
*/
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

/*
** Creates an MLX image buffer with the specified dimensions.
** Returns 0 on success, -1 on failure.
*/
static int	create_image(t_minirt *rt, t_img *img, int width, int height)
{
	img->img_ptr = mlx_new_image(rt->mlx, width, height);
	if (!img->img_ptr)
		return (-1);
	img->pixels_ptr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	img->width = width;
	img->height = height;
	return (0);
}

/*
** Initializes all MinilibX components and program state.
** Creates window, image buffers, and sets up event handlers.
*/
void	minirt_init(t_minirt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		malloc_error(rt);
	rt->win = mlx_new_window(rt->mlx, WIDTH_LOW, HEIGHT_LOW, WIN_TITLE);
	if (!rt->win)
		malloc_error(rt);
	if (create_image(rt, &rt->img, WIDTH_LOW, HEIGHT_LOW) < 0)
		malloc_error(rt);
	if (create_image(rt, &rt->img_high, WIDTH_HIGH, HEIGHT_HIGH) < 0)
		malloc_error(rt);
	rt->high_res_mode = false;
	rt->needs_render = true;
	ft_bzero(&rt->input, sizeof(t_input));
	events_init(rt);
}

/*
** Frees all allocated resources before program exit.
** Destroys images, window, display connection, and scene data.
*/
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
	scene_free(&rt->scene);
}

/*
** Resizes the window by destroying and recreating it with new dimensions.
** Also re-registers all event handlers.
*/
void	resize_window(t_minirt *rt, int width, int height)
{
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	rt->win = mlx_new_window(rt->mlx, width, height, WIN_TITLE);
	if (!rt->win)
		malloc_error(rt);
	events_init(rt);
}
