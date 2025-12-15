/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/15 20:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Interseccion rayo-esfera
** Resuelve: |O + t*D - C|^2 = r^2
** Ecuacion cuadratica: at^2 + bt + c = 0
*/
t_hit	intersect_sphere(t_ray ray, t_sphere *sp)
{
	t_hit	hit;
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t;
	double	r;

	hit = hit_new();
	r = sp->diameter / 2.0;
	oc = vec3_sub(ray.origin, sp->center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - r * r;
	disc = b * b - 4.0 * a * c;
	if (disc < 0)
		return (hit);
	t = (-b - sqrt(disc)) / (2.0 * a);
	if (t < EPSILON)
		t = (-b + sqrt(disc)) / (2.0 * a);
	if (t < EPSILON)
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = vec3_normalize(vec3_sub(hit.point, sp->center));
	hit.color = sp->color;
	return (hit);
}

/*
** Interseccion rayo-plano
** Resuelve: (O + t*D - P0) . N = 0
** t = (P0 - O) . N / (D . N)
*/
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
	return (hit);
}

/*
** Interseccion rayo-cilindro (cuerpo lateral)
** Proyecta el rayo en el plano perpendicular al eje
*/
static t_hit	intersect_cylinder_body(t_ray ray, t_cylinder *cy)
{
	t_hit	hit;
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t;
	double	r;
	double	h;

	hit = hit_new();
	r = cy->diameter / 2.0;
	oc = vec3_sub(ray.origin, cy->center);
	d_perp = vec3_sub(ray.direction,
			vec3_scale(cy->axis, vec3_dot(ray.direction, cy->axis)));
	oc_perp = vec3_sub(oc, vec3_scale(cy->axis, vec3_dot(oc, cy->axis)));
	a = vec3_dot(d_perp, d_perp);
	b = 2.0 * vec3_dot(d_perp, oc_perp);
	c = vec3_dot(oc_perp, oc_perp) - r * r;
	disc = b * b - 4.0 * a * c;
	if (disc < 0)
		return (hit);
	t = (-b - sqrt(disc)) / (2.0 * a);
	if (t < EPSILON)
		t = (-b + sqrt(disc)) / (2.0 * a);
	if (t < EPSILON)
		return (hit);
	hit.point = ray_at(ray, t);
	h = vec3_dot(vec3_sub(hit.point, cy->center), cy->axis);
	if (h < 0 || h > cy->height)
		return (hit_new());
	hit.hit = true;
	hit.t = t;
	hit.normal = vec3_normalize(vec3_sub(
				vec3_sub(hit.point, cy->center),
				vec3_scale(cy->axis, h)));
	hit.color = cy->color;
	return (hit);
}

/*
** Interseccion con las tapas del cilindro
*/
static t_hit	intersect_cylinder_caps(t_ray ray, t_cylinder *cy)
{
	t_hit		hit;
	t_hit		cap_hit;
	t_plane		cap;
	double		dist;
	double		r;

	hit = hit_new();
	r = cy->diameter / 2.0;
	cap.normal = cy->axis;
	cap.point = cy->center;
	cap.color = cy->color;
	cap_hit = intersect_plane(ray, &cap);
	if (cap_hit.hit)
	{
		dist = vec3_length(vec3_sub(cap_hit.point, cy->center));
		if (dist <= r && (cap_hit.t < hit.t))
			hit = cap_hit;
	}
	cap.point = vec3_add(cy->center, vec3_scale(cy->axis, cy->height));
	cap_hit = intersect_plane(ray, &cap);
	if (cap_hit.hit)
	{
		dist = vec3_length(vec3_sub(cap_hit.point, cap.point));
		if (dist <= r && (cap_hit.t < hit.t))
			hit = cap_hit;
	}
	return (hit);
}

/*
** Interseccion rayo-cilindro completa (cuerpo + tapas)
*/
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

/*
** Encuentra el impacto mas cercano con cualquier objeto de la escena
*/
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
		else
			current = hit_new();
		if (current.hit && current.t < closest.t)
			closest = current;
		i++;
	}
	return (closest);
}
