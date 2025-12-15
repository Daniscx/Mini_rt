/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 14:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

#define CHECKER_SCALE 2.0
#define SPECULAR_EXP 32.0
#define SPECULAR_STRENGTH 0.5

/*
** Applies checkerboard pattern to hit point for planes.
** Alternates between original color and a darker version.
*/
t_vec3	apply_checkerboard(t_hit *hit)
{
	int		u;
	int		v;
	t_vec3	dark;

	u = (int)floor(hit->point.x / CHECKER_SCALE);
	v = (int)floor(hit->point.z / CHECKER_SCALE);
	if ((u + v) % 2 == 0)
		return (hit->color);
	dark = vec3_scale(hit->color, 0.3);
	return (dark);
}

/*
** Verifica si un punto esta en sombra respecto a una luz.
** Lanza un rayo desde el punto hacia la luz y verifica interseccion.
*/
bool	is_in_shadow(t_vec3 point, t_vec3 light_dir, double light_dist,
			t_scene *scene)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.origin = vec3_add(point, vec3_scale(light_dir, EPSILON * 10));
	shadow_ray.direction = light_dir;
	hit = find_closest_hit(shadow_ray, scene);
	if (hit.hit && hit.t < light_dist)
		return (true);
	return (false);
}

/*
** Calculates specular component using Phong model.
** reflect_dir = 2 * (N . L) * N - L
** specular = (R . V)^n * intensity
*/
static t_vec3	calculate_specular(t_hit hit, t_light *light, t_vec3 view_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	double	spec;
	double	dot_nl;

	if (hit.specular <= 0)
		return (vec3_new(0, 0, 0));
	light_dir = vec3_normalize(vec3_sub(light->position, hit.point));
	dot_nl = vec3_dot(hit.normal, light_dir);
	if (dot_nl < 0)
		return (vec3_new(0, 0, 0));
	reflect_dir = vec3_sub(vec3_scale(hit.normal, 2.0 * dot_nl), light_dir);
	reflect_dir = vec3_normalize(reflect_dir);
	spec = vec3_dot(reflect_dir, view_dir);
	if (spec < 0)
		spec = 0;
	spec = pow(spec, SPECULAR_EXP) * SPECULAR_STRENGTH * light->brightness;
	return (vec3_scale(light->color, spec));
}

/*
** Calcula la componente difusa de la iluminacion (modelo Lambert).
** diffuse = object_color * light_color * brightness * max(0, N . L)
*/
static t_vec3	calculate_diffuse(t_hit hit, t_light *light, t_scene *scene)
{
	t_vec3	light_dir;
	double	light_dist;
	double	diff;
	t_vec3	diffuse;

	light_dir = vec3_sub(light->position, hit.point);
	light_dist = vec3_length(light_dir);
	light_dir = vec3_normalize(light_dir);
	if (is_in_shadow(hit.point, light_dir, light_dist, scene))
		return (vec3_new(0, 0, 0));
	diff = vec3_dot(hit.normal, light_dir);
	if (diff < 0)
		diff = 0;
	diffuse = vec3_mult(hit.color, light->color);
	return (vec3_scale(diffuse, diff * light->brightness));
}

/*
** Calcula el color final de un punto usando modelo de iluminacion:
** Color = Ambiente + Difuso + Especular (Phong model)
** Supports colored lights and multiple light sources.
*/
t_vec3	calculate_lighting(t_hit hit, t_scene *scene, t_vec3 view_dir)
{
	t_vec3	result;
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	int		i;

	if (hit.checkerboard)
		hit.color = apply_checkerboard(&hit);
	ambient = vec3_mult(hit.color, scene->ambient.color);
	ambient = vec3_scale(ambient, scene->ambient.ratio);
	result = ambient;
	i = 0;
	while (i < scene->light_count)
	{
		diffuse = calculate_diffuse(hit, &scene->lights[i], scene);
		specular = calculate_specular(hit, &scene->lights[i], view_dir);
		result = vec3_add(result, diffuse);
		result = vec3_add(result, specular);
		i++;
	}
	return (result);
}
