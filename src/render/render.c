/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 08:51:15 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Writes a pixel color directly to the image buffer.
** Validates coordinates are within image bounds.
*/
static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
** Converts RGB components (0-255) to a single integer color value.
** Format: 0x00RRGGBB
*/
static int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/*
** Clears the image buffer to black.
*/
static void	clear_image(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

/*
** Traces a ray through the scene and computes the pixel color.
** Returns black if no intersection, otherwise computes lighting.
*/
static int	trace_ray(t_ray ray, t_scene *scene)
{
	t_hit	hit;
	t_vec3	color;
	t_vec3	view_dir;
	int		r;
	int		g;
	int		b;

	hit = find_closest_hit(ray, scene);
	if (!hit.hit)
		return (create_rgb(0, 0, 0));
	view_dir = vec3_negate(ray.direction);
	color = calculate_lighting(hit, scene, view_dir);
	r = (int)(vec3_clamp(color.x, 0.0, 1.0) * 255.0);
	g = (int)(vec3_clamp(color.y, 0.0, 1.0) * 255.0);
	b = (int)(vec3_clamp(color.z, 0.0, 1.0) * 255.0);
	return (create_rgb(r, g, b));
}

/*
** Renders the scene at low resolution for interactive viewing.
** Uses the standard image buffer.
*/
void	render_scene(t_minirt *rt)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;

	rt->scene.camera.aspect_ratio = (double)rt->img.width / rt->img.height;
	y = 0;
	while (y < rt->img.height)
	{
		x = 0;
		while (x < rt->img.width)
		{
			ray = ray_from_camera(&rt->scene.camera, x, y, &rt->img);
			color = trace_ray(ray, &rt->scene);
			put_pixel(&rt->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
}

/*
** Renders the scene at high resolution and displays it in a full-size window.
** Mouse capture is disabled during high-res rendering.
*/
void	render_high_res(t_minirt *rt)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;

	ft_putstr_fd("\n\033[1;35m[HIGH QUALITY MODE]\033[1;0m", 0);
	ft_printf(" Rendering at %dx%d!\n", WIDTH_HIGH, HEIGHT_HIGH);
	if (rt->input.mouse_captured)
	{
		rt->input.mouse_captured = false;
		mlx_mouse_show(rt->mlx, rt->win);
	}
	ft_bzero(rt->input.keys, sizeof(rt->input.keys));
	resize_window(rt, WIDTH_HIGH, HEIGHT_HIGH);
	clear_image(&rt->img_high);
	rt->scene.camera.aspect_ratio = (double)rt->img_high.width / rt->img_high.height;
	y = -1;
	while (++y < rt->img_high.height)
	{
		if (y % 100 == 0)
		{
			printf("\r - Progress: %d%%", y / 10);
			fflush(stdout);
		}
		x = -1;
		while (++x < rt->img_high.width)
		{
			ray = ray_from_camera(&rt->scene.camera, x, y, &rt->img_high);
			color = trace_ray(ray, &rt->scene);
			put_pixel(&rt->img_high, x, y, color);
		}
	}
	ft_printf("\n");
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img_high.img_ptr, 0, 0);
	ft_putstr_fd("\033[1;35m[HIGH QUALITY MODE]\033[1;0m", 0);
	ft_printf(" Render complete! Press 'P' to return to low resolution.\n\n");
	rt->high_res_mode = true;
}

/*
** Returns to low resolution mode.
** Ensures mouse is visible and not captured.
*/
void	render_low_res(t_minirt *rt)
{
	ft_putstr_fd("\033[1;36m[NAVIGATION MODE]\033[1;0m", 0);
	ft_printf(" Switching to %dx%d...\n\n", WIDTH_LOW, HEIGHT_LOW);
	if (rt->input.mouse_captured)
	{
		rt->input.mouse_captured = false;
		mlx_mouse_show(rt->mlx, rt->win);
	}
	ft_bzero(rt->input.keys, sizeof(rt->input.keys));
	resize_window(rt, WIDTH_LOW, HEIGHT_LOW);
	rt->high_res_mode = false;
	rt->scene.camera.aspect_ratio = (double)rt->img.width / rt->img.height;
	rt->needs_render = true;
	render_scene(rt);
}
