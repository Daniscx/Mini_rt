/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 17:31:33 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Writes a pixel color to the image buffer at the specified coordinates.
** Performs bounds checking to prevent buffer overflow.
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
** Packs RGB color components into a single 32-bit integer.
*/
static int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/*
** Fills the entire image buffer with black pixels.
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
** Traces a ray through the scene and returns the color at the hit point.
** Returns black if no intersection is found.
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
** Renders the scene at low resolution for real-time navigation.
** Iterates over each pixel and traces rays from camera.
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
** Renders scene at high resolution. Disables input, resizes window,
** and displays progress. Used for final quality screenshots.
*/
void	render_high_res(t_minirt *rt)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;

	ft_putstr_fd("\n\033[1;35m[HIGH QUALITY RENDER]\033[1;0m", 0);
	ft_printf(" Rendering at %dx%d!\n", WIDTH_HIGH, HEIGHT_HIGH);
	ft_bzero(&rt->input, sizeof(t_input));
	rt->input.selected_obj = -1;
	resize_window(rt, WIDTH_HIGH, HEIGHT_HIGH);
	mlx_mouse_show(rt->mlx, rt->win);
	clear_image(&rt->img_high);
	rt->scene.camera.aspect_ratio = (double)rt->img_high.width / rt->img_high.height;
	y = -1;
	while (++y < rt->img_high.height)
	{
		if (y % 100 == 0)
		{
			printf("\r - Progress: %d%%", (y * 100) / rt->img_high.height);
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
	printf("\r - Progress: 100%%\n");
	fflush(stdout);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img_high.img_ptr, 0, 0);
	ft_putstr_fd("\033[1;35m[HIGH QUALITY RENDER]\033[1;0m", 0);
	ft_printf(" Render complete! Press ");
	ft_putstr_fd("\033[1;31m'esc'\033[1;0m", 0);
	ft_printf(" to exit!\n");
	rt->high_res_mode = true;
}

/*
** Switches back to low resolution navigation mode. Resets input state,
** resizes window and triggers a re-render.
*/
void	render_low_res(t_minirt *rt)
{
	ft_putstr_fd("\033[1;36m[NAVIGATION MODE]\033[1;0m", 0);
	ft_printf(" Switching to %dx%d...\n", WIDTH_LOW, HEIGHT_LOW);
	ft_bzero(&rt->input, sizeof(t_input));
	rt->input.selected_obj = -1;
	resize_window(rt, WIDTH_LOW, HEIGHT_LOW);
	mlx_mouse_show(rt->mlx, rt->win);
	rt->high_res_mode = false;
	rt->scene.camera.aspect_ratio = (double)rt->img.width / rt->img.height;
	rt->needs_render = true;
	render_scene(rt);
}
