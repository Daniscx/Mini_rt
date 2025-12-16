/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 16:24:54 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <X11/Xlib.h>

typedef struct s_xvar_internal
{
	Display		*display;
	Window		root;
	int			screen;
}				t_xvar_internal;

typedef struct s_win_list_internal
{
	Window		window;
}				t_win_list_internal;

static void	center_window(t_minirt *rt, int width, int height)
{
	Display	*display;
	int		screen_width;
	int		screen_height;
	int		x;
	int		y;

	display = ((t_xvar_internal *)rt->mlx)->display;
	screen_width = DisplayWidth(display, DefaultScreen(display));
	screen_height = DisplayHeight(display, DefaultScreen(display));
	x = (screen_width - width) / 2;
	y = (screen_height - height) / 2;
	XMoveWindow(display, ((t_win_list_internal *)rt->win)->window, x, y);
	XFlush(display);
}

static void	events_init(t_minirt *rt)
{
	mlx_hook(rt->win, KeyPress, KeyPressMask, key_press_handler, rt);
	mlx_hook(rt->win, KeyRelease, KeyReleaseMask, key_release_handler, rt);
	mlx_hook(rt->win, ButtonPress, ButtonPressMask, mouse_press_handler, rt);
	mlx_hook(rt->win, ButtonRelease, ButtonReleaseMask, mouse_release_handler, rt);
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

void	minirt_init(t_minirt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		malloc_error(rt);
	rt->win = mlx_new_window(rt->mlx, WIDTH_LOW, HEIGHT_LOW, WIN_TITLE);
	if (!rt->win)
		malloc_error(rt);
	center_window(rt, WIDTH_LOW, HEIGHT_LOW);
	if (create_image(rt, &rt->img, WIDTH_LOW, HEIGHT_LOW) < 0)
		malloc_error(rt);
	if (create_image(rt, &rt->img_high, WIDTH_HIGH, HEIGHT_HIGH) < 0)
		malloc_error(rt);
	rt->high_res_mode = false;
	rt->needs_render = true;
	ft_bzero(&rt->input, sizeof(t_input));
	rt->input.selected_obj = -1;
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
	scene_free(&rt->scene);
}

void	resize_window(t_minirt *rt, int width, int height)
{
	Display	*display;

	display = ((t_xvar_internal *)rt->mlx)->display;
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	rt->win = mlx_new_window(rt->mlx, width, height, WIN_TITLE);
	if (!rt->win)
		malloc_error(rt);
	center_window(rt, width, height);
	XSync(display, False);
	events_init(rt);
	XSync(display, False);
}

void	warp_mouse_center(t_minirt *rt)
{
	Display	*display;
	Window	window;

	display = ((t_xvar_internal *)rt->mlx)->display;
	window = ((t_win_list_internal *)rt->win)->window;
	XWarpPointer(display, None, window, 0, 0, 0, 0,
		WIDTH_LOW / 2, HEIGHT_LOW / 2);
	XSync(display, False);
}
