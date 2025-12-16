/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 10:43:28 by ravazque         ###   ########.fr       */
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

/*
** Centers the window on the screen using X11 display dimensions.
*/
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

/*
** Registers all MLX event hooks for keyboard, mouse and window events.
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
** Handles memory allocation errors. Cleans up and exits with error message.
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
** Initializes MLX, window, images and event handlers.
** Creates both low and high resolution image buffers.
*/
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
	events_init(rt);
}

/*
** Frees all allocated resources: images, window, MLX and scene data.
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
** Destroys current window and creates a new one with given dimensions.
** Re-registers event hooks and centers the new window.
*/
void	resize_window(t_minirt *rt, int width, int height)
{
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	rt->win = mlx_new_window(rt->mlx, width, height, WIN_TITLE);
	if (!rt->win)
		malloc_error(rt);
	center_window(rt, width, height);
	events_init(rt);
}
