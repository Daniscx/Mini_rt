/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 10:43:43 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Creates a new ray with given origin and direction. Direction is normalized.
*/
t_ray	ray_new(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec3_normalize(direction);
	return (ray);
}

/*
** Returns the point along the ray at parameter t: origin + t * direction.
*/
t_vec3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}

/*
** Generates a ray from camera through the pixel at screen coordinates (x,y).
** Uses FOV and aspect ratio to calculate ray direction in world space.
*/
t_ray	ray_from_camera(t_camera *cam, int x, int y, t_img *img)
{
	double	u;
	double	v;
	double	fov_scale;
	t_vec3	dir;

	fov_scale = tan((cam->fov * M_PI / 180.0) / 2.0);
	u = (2.0 * ((double)x + 0.5) / (double)img->width - 1.0) * cam->aspect_ratio;
	v = 1.0 - 2.0 * ((double)y + 0.5) / (double)img->height;
	u *= fov_scale;
	v *= fov_scale;
	dir = vec3_add(cam->direction,
			vec3_add(vec3_scale(cam->right, u), vec3_scale(cam->up, v)));
	return (ray_new(cam->position, dir));
}
