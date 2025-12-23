/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 03:22:41 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/escene.h"
# include "../../includes/minirt.h"

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

void	render_scene(t_minirt *rt)
{
	int		x;
	int		y;
	t_ray	ray;

	rt->scene->camera->aspect_ratio = (double)rt->img.width / rt->img.height;
	y = -1;
	while (++y < rt->img.height)
	{
		x = -1;
		while (++x < rt->img.width)
		{
			ray = ray_from_camera(rt->scene->camera, x, y, &rt->img);
			put_pixel(&rt->img, x, y, trace_ray(ray, rt->scene));
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
	XFlush(((t_xvar *)rt->mlx)->display);
}
