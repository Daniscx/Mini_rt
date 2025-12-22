/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_high.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/22 14:48:12 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	trace_ray(t_ray ray, t_scene *scene)
{
	t_hit	hit;
	t_vec3	color;
	t_vec3	view_dir;

	hit = find_closest_hit(ray, scene);
	if (!hit.hit)
		return (0);
	view_dir = vec3_negate(ray.direction);
	color = calculate_lighting(hit, scene, view_dir);
	return (vec3_to_color(color));
}

static void	render_row(t_minirt *rt, int y)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < rt->img_high.width)
	{
		ray = ray_from_camera(rt->scene->camera, x, y, &rt->img_high);
		put_pixel(&rt->img_high, x, y, trace_ray(ray, rt->scene));
	}
}

static void	print_progress(int y, int height)
{
	if (y % 100 == 0)
	{
		printf("\r - Progress: %d%%", (y * 100) / height);
		fflush(stdout);
	}
}

void	render_high_res(t_minirt *rt)
{
	int		y;
	char	filename[256];

	ft_printf("\n\033[1;35m[SCREENSHOT]\033[0m Rendering at %dx%d...\n",
		rt->img_high.width, rt->img_high.height);
	rt->scene->camera->aspect_ratio = (double)rt->img_high.width
		/ rt->img_high.height;
	y = -1;
	while (++y < rt->img_high.height)
	{
		print_progress(y, rt->img_high.height);
		render_row(rt, y);
	}
	printf("\r - Progress: 100%%\n");
	generate_filename(filename);
	if (save_bmp(&rt->img_high, filename))
		ft_printf("\033[1;35m[SAVED]\033[0m %s\n", filename);
	else
		ft_printf("\033[1;35m[ERROR]\033[0m Failed to save screenshot\n");
	rt->scene->camera->aspect_ratio = (double)rt->img.width / rt->img.height;
}
