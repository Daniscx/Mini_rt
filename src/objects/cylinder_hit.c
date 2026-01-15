/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:47:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:19:27 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"

static t_hit	build_body_hit(t_ray ray, t_cylinder *cy, double t)
{
	t_hit	hit;
	double	h;

	hit = hit_new();
	if (t < EPSILON)
		return (hit);
	hit.point = ray_at(ray, t);
	h = vec3_dot(vec3_sub(hit.point, cy->center), cy->axis);
	if (h < 0 || h > cy->height)
		return (hit_new());
	hit.hit = true;
	hit.t = t;
	hit.normal = vec3_normalize(vec3_sub(vec3_sub(hit.point, cy->center),
				vec3_scale(cy->axis, h)));
	hit.color = cy->color;
	hit.specular = 1.0;
	return (hit);
}

static t_hit	intersect_cylinder_body(t_ray ray, t_cylinder *cy)
{
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	coef[3];
	double	disc;

	oc = vec3_sub(ray.origin, cy->center);
	d_perp = vec3_sub(ray.direction, vec3_scale(cy->axis,
				vec3_dot(ray.direction, cy->axis)));
	oc_perp = vec3_sub(oc, vec3_scale(cy->axis, vec3_dot(oc, cy->axis)));
	coef[0] = vec3_dot(d_perp, d_perp);
	coef[1] = 2.0 * vec3_dot(d_perp, oc_perp);
	coef[2] = vec3_dot(oc_perp, oc_perp)
		- (cy->diameter / 2.0) * (cy->diameter / 2.0);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit_new());
	coef[0] = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	if (coef[0] < EPSILON)
		coef[0] = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	return (build_body_hit(ray, cy, coef[0]));
}

static t_hit	intersect_cylinder_caps(t_ray ray, t_cylinder *cy)
{
	t_hit	hit;
	t_hit	cap_hit;
	t_plane	cap;
	double	dist;

	hit = hit_new();
	cap.normal = cy->axis;
	cap.point = cy->center;
	cap.color = cy->color;
	cap_hit = intersect_plane(ray, &cap);
	if (cap_hit.hit)
	{
		dist = vec3_length(vec3_sub(cap_hit.point, cy->center));
		if (dist <= cy->diameter / 2.0 && cap_hit.t < hit.t)
			hit = cap_hit;
	}
	cap.point = vec3_add(cy->center, vec3_scale(cy->axis, cy->height));
	cap_hit = intersect_plane(ray, &cap);
	if (cap_hit.hit)
	{
		dist = vec3_length(vec3_sub(cap_hit.point, cap.point));
		if (dist <= cy->diameter / 2.0 && cap_hit.t < hit.t)
			hit = cap_hit;
	}
	return (hit);
}

t_hit	intersect_cylinder(t_ray ray, void *cylinder)
{
	t_cylinder	*cy;
	t_hit		body_hit;
	t_hit		caps_hit;

	cy = (t_cylinder *)cylinder;
	body_hit = intersect_cylinder_body(ray, cy);
	caps_hit = intersect_cylinder_caps(ray, cy);
	if (!body_hit.hit && !caps_hit.hit)
		return (hit_new());
	if (body_hit.hit && (!caps_hit.hit || body_hit.t < caps_hit.t))
		return (body_hit);
	return (caps_hit);
}
