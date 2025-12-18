/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/18 12:26:59 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_hit	hit_new(void)
{
	t_hit	hit;

	hit.hit = false;
	hit.t = INFINITY;
	hit.point = vec3_new(0, 0, 0);
	hit.normal = vec3_new(0, 1, 0);
	hit.color = vec3_new(0, 0, 0);
	hit.specular = 1.0;
	hit.checkerboard = 0;
	hit.u = 0;
	hit.v = 0;
	hit.texture = NULL;
	hit.bump_map = NULL;
	return (hit);
}

t_hit	intersect_sphere(t_ray ray, t_sphere *sp)
{
	t_hit	hit;
	t_vec3	oc;
	double	coef[3];
	double	disc;
	double	t;

	hit = hit_new();
	oc = vec3_sub(ray.origin, sp->center);
	coef[0] = vec3_dot(ray.direction, ray.direction);
	coef[1] = 2.0 * vec3_dot(oc, ray.direction);
	coef[2] = vec3_dot(oc, oc) - (sp->diameter / 2.0) * (sp->diameter / 2.0);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit);
	t = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		t = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = vec3_normalize(vec3_sub(hit.point, sp->center));
	hit.color = sp->color;
	hit.specular = 1.0;
	hit.texture = sp->texture;
	hit.bump_map = sp->bump_map;
	sphere_get_uv(hit.point, sp->center, &hit.u, &hit.v);
	return (hit);
}

t_hit	intersect_plane(t_ray ray, t_plane *pl)
{
	t_hit	hit;
	double	denom;
	double	t;

	hit = hit_new();
	denom = vec3_dot(ray.direction, pl->normal);
	if (fabs(denom) < EPSILON)
		return (hit);
	t = vec3_dot(vec3_sub(pl->point, ray.origin), pl->normal) / denom;
	if (t < EPSILON)
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = pl->normal;
	if (denom > 0)
		hit.normal = vec3_negate(hit.normal);
	hit.color = pl->color;
	hit.specular = 0.3;
	return (hit);
}

static t_hit	intersect_cylinder_body(t_ray ray, t_cylinder *cy)
{
	t_hit	hit;
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	coef[3];
	double	disc;
	double	t;
	double	h;

	hit = hit_new();
	oc = vec3_sub(ray.origin, cy->center);
	d_perp = vec3_sub(ray.direction, vec3_scale(cy->axis, vec3_dot(ray.direction, cy->axis)));
	oc_perp = vec3_sub(oc, vec3_scale(cy->axis, vec3_dot(oc, cy->axis)));
	coef[0] = vec3_dot(d_perp, d_perp);
	coef[1] = 2.0 * vec3_dot(d_perp, oc_perp);
	coef[2] = vec3_dot(oc_perp, oc_perp) - (cy->diameter / 2.0) * (cy->diameter / 2.0);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit);
	t = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		t = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		return (hit);
	hit.point = ray_at(ray, t);
	h = vec3_dot(vec3_sub(hit.point, cy->center), cy->axis);
	if (h < 0 || h > cy->height)
		return (hit_new());
	hit.hit = true;
	hit.t = t;
	hit.normal = vec3_normalize(vec3_sub(vec3_sub(hit.point, cy->center), vec3_scale(cy->axis, h)));
	hit.color = cy->color;
	hit.specular = 1.0;
	return (hit);
}

static t_hit	intersect_cylinder_caps(t_ray ray, t_cylinder *cy)
{
	t_hit		hit;
	t_hit		cap_hit;
	t_plane		cap;
	double		dist;

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

t_hit	intersect_cylinder(t_ray ray, t_cylinder *cy)
{
	t_hit	body_hit;
	t_hit	caps_hit;

	body_hit = intersect_cylinder_body(ray, cy);
	caps_hit = intersect_cylinder_caps(ray, cy);
	if (!body_hit.hit && !caps_hit.hit)
		return (hit_new());
	if (body_hit.hit && (!caps_hit.hit || body_hit.t < caps_hit.t))
		return (body_hit);
	return (caps_hit);
}

static t_hit	cone_body_hit(t_ray ray, t_cone *co, double t, t_vec3 tip, double cos2)
{
	t_hit	hit;
	double	h;

	hit = hit_new();
	if (t < EPSILON)
		return (hit);
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

static t_hit	intersect_cone_body(t_ray ray, t_cone *co)
{
	t_vec3	tip;
	t_vec3	oc;
	double	cos2;
	double	coef[3];
	double	disc;
	double	t[2];
	double	dv;
	double	ocv;
	t_hit	hit1;
	t_hit	hit2;

	tip = vec3_add(co->apex, vec3_scale(co->axis, co->height));
	cos2 = cos(co->angle * M_PI / 180.0);
	cos2 = cos2 * cos2;
	oc = vec3_sub(ray.origin, tip);
	dv = vec3_dot(ray.direction, co->axis);
	ocv = vec3_dot(oc, co->axis);
	coef[0] = dv * dv - cos2 * vec3_dot(ray.direction, ray.direction);
	coef[1] = 2.0 * (dv * ocv - cos2 * vec3_dot(ray.direction, oc));
	coef[2] = ocv * ocv - cos2 * vec3_dot(oc, oc);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit_new());
	t[0] = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	t[1] = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	hit1 = cone_body_hit(ray, co, t[0], tip, cos2);
	hit2 = cone_body_hit(ray, co, t[1], tip, cos2);
	if (hit1.hit && (!hit2.hit || hit1.t < hit2.t))
		return (hit1);
	if (hit2.hit)
		return (hit2);
	return (hit_new());
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

t_hit	find_closest_hit(t_ray ray, t_scene *scene)
{
	t_hit	closest;
	t_hit	current;
	int		i;

	closest = hit_new();
	i = 0;
	while (i < scene->object_count)
	{
		if (scene->objects[i].type == OBJ_SPHERE)
			current = intersect_sphere(ray, &scene->objects[i].sphere);
		else if (scene->objects[i].type == OBJ_PLANE)
			current = intersect_plane(ray, &scene->objects[i].plane);
		else if (scene->objects[i].type == OBJ_CYLINDER)
			current = intersect_cylinder(ray, &scene->objects[i].cylinder);
		else if (scene->objects[i].type == OBJ_CONE)
			current = intersect_cone(ray, &scene->objects[i].cone);
		else
			current = hit_new();
		if (current.hit && current.t < closest.t)
		{
			closest = current;
			closest.checkerboard = scene->objects[i].checkerboard;
		}
		i++;
	}
	return (closest);
}
