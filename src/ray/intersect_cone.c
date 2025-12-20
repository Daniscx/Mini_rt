/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:45:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:10:26 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_hit	cone_body_hit(t_ray ray, t_cone *co, double t, double cos2)
{
	t_hit	hit;
	double	h;
	t_vec3	tip;

	hit = hit_new();
	if (t < EPSILON)
		return (hit);
	tip = vec3_add(co->apex, vec3_scale(co->axis, co->height));
	hit.point = ray_at(ray, t);
	h = vec3_dot(vec3_sub(hit.point, tip), co->axis);
	if (h > 0 || h < -co->height)
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.normal = vec3_sub(hit.point, tip);
	hit.normal = vec3_sub(hit.normal, vec3_scale(co->axis, vec3_dot(hit.normal, co->axis) / cos2));
	hit.normal = vec3_normalize(hit.normal);
	hit.color = co->color;
	hit.specular = 1.0;
	return (hit);
}

static void	calc_cone_coeffs(t_ray ray, t_cone *co, double *coef, double cos2)
{
	t_vec3	tip;
	t_vec3	oc;
	double	dv;
	double	ocv;

	tip = vec3_add(co->apex, vec3_scale(co->axis, co->height));
	oc = vec3_sub(ray.origin, tip);
	dv = vec3_dot(ray.direction, co->axis);
	ocv = vec3_dot(oc, co->axis);
	coef[0] = dv * dv - cos2 * vec3_dot(ray.direction, ray.direction);
	coef[1] = 2.0 * (dv * ocv - cos2 * vec3_dot(ray.direction, oc));
	coef[2] = ocv * ocv - cos2 * vec3_dot(oc, oc);
}

static t_hit	intersect_cone_body(t_ray ray, t_cone *co)
{
	double	cos2;
	double	coef[3];
	double	disc;
	double	t[2];
	t_hit	hit1;

	cos2 = cos(co->angle * M_PI / 180.0);
	cos2 = cos2 * cos2;
	calc_cone_coeffs(ray, co, coef, cos2);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit_new());
	t[0] = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	t[1] = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	hit1 = cone_body_hit(ray, co, t[0], cos2);
	if (hit1.hit)
		return (hit1);
	return (cone_body_hit(ray, co, t[1], cos2));
}

static t_hit	intersect_cone_cap(t_ray ray, t_cone *co)
{
	t_hit	hit;
	t_hit	cap_hit;
	t_plane	cap;
	double	dist;
	double	radius;

	hit = hit_new();
	radius = co->height * tan(co->angle * M_PI / 180.0);
	cap.normal = co->axis;
	cap.point = co->apex;
	cap.color = co->color;
	cap_hit = intersect_plane(ray, &cap);
	if (cap_hit.hit)
	{
		dist = vec3_length(vec3_sub(cap_hit.point, co->apex));
		if (dist <= radius)
			hit = cap_hit;
	}
	return (hit);
}

t_hit	intersect_cone(t_ray ray, t_cone *co)
{
	t_hit	body_hit;
	t_hit	cap_hit;

	body_hit = intersect_cone_body(ray, co);
	cap_hit = intersect_cone_cap(ray, co);
	if (!body_hit.hit && !cap_hit.hit)
		return (hit_new());
	if (body_hit.hit && (!cap_hit.hit || body_hit.t < cap_hit.t))
		return (body_hit);
	return (cap_hit);
}
