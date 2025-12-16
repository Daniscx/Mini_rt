/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 02:47:37 by ravazque         ###   ########.fr       */
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

// /*
// ** Gets pixel color from image buffer.
// ** Returns 0 if coordinates are out of bounds.
// */
// static int	get_pixel(t_img *img, int x, int y)
// {
// 	char	*src;

// 	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
// 		return (0);
// 	src = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
// 	return (*(unsigned int *)src);
// }

// /*
// ** Downscales high resolution image to low resolution using box filter.
// ** Averages colors in each block for antialiasing effect.
// */
// static void	downscale_image(t_img *src, t_img *dst)
// {
// 	int		dx;
// 	int		dy;
// 	int		sx;
// 	int		sy;
// 	float	scale_x;
// 	float	scale_y;
// 	int		color;
// 	int		r;
// 	int		g;
// 	int		b;
// 	int		count;
// 	int		sample_x;
// 	int		sample_y;

// 	scale_x = (float)src->width / dst->width;
// 	scale_y = (float)src->height / dst->height;
// 	dy = 0;
// 	while (dy < dst->height)
// 	{
// 		dx = 0;
// 		while (dx < dst->width)
// 		{
// 			r = 0;
// 			g = 0;
// 			b = 0;
// 			count = 0;
// 			sample_y = 0;
// 			while (sample_y < (int)scale_y)
// 			{
// 				sample_x = 0;
// 				while (sample_x < (int)scale_x)
// 				{
// 					sx = (int)(dx * scale_x) + sample_x;
// 					sy = (int)(dy * scale_y) + sample_y;
// 					if (sx < src->width && sy < src->height)
// 					{
// 						color = get_pixel(src, sx, sy);
// 						r += (color >> 16) & 0xFF;
// 						g += (color >> 8) & 0xFF;
// 						b += color & 0xFF;
// 						count++;
// 					}
// 					sample_x++;
// 				}
// 				sample_y++;
// 			}
// 			if (count > 0)
// 			{
// 				r /= count;
// 				g /= count;
// 				b /= count;
// 			}
// 			put_pixel(dst, dx, dy, create_rgb(r, g, b));
// 			dx++;
// 		}
// 		dy++;
// 	}
// }

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
** Renders the scene at high resolution for quality screenshots.
** Shows black screen during render, then 10 second countdown.
*/
void	render_high_res(t_minirt *rt)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;
	int		countdown;

	ft_putstr_fd("\n\033[1;35m[HIGH QUALITY MODE]\033[1;0m", 0);
	ft_printf(" Rendering at %dx%d!\n", WIDTH_HIGH, HEIGHT_HIGH);
	clear_image(&rt->img_high);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img_high.img_ptr, 0, 0);
	rt->scene.camera.aspect_ratio = (double)rt->img_high.width
		/ rt->img_high.height;
	y = -1;
	while (++y < rt->img_high.height)
	{
		x = -1;
		while (++x < rt->img_high.width)
		{
			ray = ray_from_camera(&rt->scene.camera, x, y, &rt->img_high);
			color = trace_ray(ray, &rt->scene);
			put_pixel(&rt->img_high, x, y, color);
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img_high.img_ptr, 0, 0);
	ft_putstr_fd("\033[1;35m[HIGH QUALITY MODE]\033[1;0m", 0);
	ft_printf(" Render complete! Countdown: ");
	countdown = 10;
	while (countdown > 0)
	{
		ft_printf("%d... ", countdown);
		sleep(1);
		countdown--;
	}
	ft_putstr_fd("\n\033[1;35m[HIGH QUALITY MODE]\033[1;0m", 0);
	ft_printf(" Returning to navigation mode.\n\n");
	rt->high_res_mode = false;
	rt->scene.camera.aspect_ratio = (double)rt->img.width / rt->img.height;
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
}
