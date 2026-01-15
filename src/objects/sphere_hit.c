/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:49:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:18:05 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"

static t_hit	sphere_calc_hit(t_ray ray, t_sphere *sp, double t)
{
	t_hit	hit;

	hit = hit_new();
	hit.hit = true;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = vec3_normalize(vec3_sub(hit.point, sp->center));
	hit.color = sp->color;
	hit.specular = 1.0;
	hit.texture = sp->texture;
	hit.bump_map = sp->bump_map;
	if (hit.texture || hit.bump_map)
		sphere_get_uv(hit.point, sp->center, &hit.u, &hit.v);
	return (hit);
}

static double	sphere_solve_t(double *coef, double disc)
{
	double	t;

	t = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		t = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	return (t);
}

t_hit	intersect_sphere(t_ray ray, void *sphere)
{
	t_hit		hit;
	t_vec3		oc;
	double		coef[3];
	double		disc;
	double		t;

	hit = hit_new();
	oc = vec3_sub(ray.origin, ((t_sphere *)sphere)->center);
	coef[0] = vec3_dot(ray.direction, ray.direction);
	coef[1] = 2.0 * vec3_dot(oc, ray.direction);
	coef[2] = vec3_dot(oc, oc) - pow(((t_sphere *)sphere)->diameter / 2.0, 2);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit);
	t = sphere_solve_t(coef, disc);
	if (t < EPSILON)
		return (hit);
	return (sphere_calc_hit(ray, (t_sphere *)sphere, t));
}
