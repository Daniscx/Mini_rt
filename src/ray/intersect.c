/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:10:16 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static double	solve_sphere_t(t_ray ray, t_sphere *sp)
{
	t_vec3	oc;
	double	coef[3];
	double	disc;
	double	t;

	oc = vec3_sub(ray.origin, sp->center);
	coef[0] = vec3_dot(ray.direction, ray.direction);
	coef[1] = 2.0 * vec3_dot(oc, ray.direction);
	coef[2] = vec3_dot(oc, oc) - (sp->diameter / 2.0) * (sp->diameter / 2.0);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (-1.0);
	t = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		t = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		return (-1.0);
	return (t);
}

t_hit	intersect_sphere(t_ray ray, t_sphere *sp)
{
	t_hit	hit;
	double	t;

	hit = hit_new();
	t = solve_sphere_t(ray, sp);
	if (t < 0)
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

static t_hit	get_object_hit(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, &obj->sphere));
	else if (obj->type == OBJ_PLANE)
		return (intersect_plane(ray, &obj->plane));
	else if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder(ray, &obj->cylinder));
	else if (obj->type == OBJ_CONE)
		return (intersect_cone(ray, &obj->cone));
	return (hit_new());
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
		current = get_object_hit(ray, &scene->objects[i]);
		if (current.hit && current.t < closest.t)
		{
			closest = current;
			closest.checkerboard = scene->objects[i].checkerboard;
		}
		i++;
	}
	return (closest);
}
