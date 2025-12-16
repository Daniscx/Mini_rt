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
** Checks if a point is in shadow relative to a light source.
** Casts a ray from the point towards the light and checks for intersection.
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
** Calculates the diffuse component of lighting (Lambert model).
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
** Calculates the final color of a point using lighting model:
** Color = Ambient + Diffuse + Specular (Phong model)
** Supports colored lights and multiple light sources.
*/
/*
** [ADVANCED FEATURE - Currently disabled]
** Calculates indirect lighting (color bleeding) by sampling the hemisphere.
** When enabled, light bounces off objects and picks up their color,
** creating realistic color interactions (e.g., red wall tints nearby objects).
**
** To enable: Uncomment ENABLE_COLOR_BLEEDING in minirt.h
*/
#ifdef ENABLE_COLOR_BLEEDING
static t_vec3	calculate_color_bleeding(t_hit hit, t_scene *scene)
{
	t_vec3	result;
	t_vec3	sample_dir;
	t_ray	bounce_ray;
	t_hit	bounce_hit;
	int		samples;
	int		i;

	result = vec3_new(0, 0, 0);
	samples = 8;
	i = 0;
	while (i < samples)
	{
		sample_dir = vec3_normalize(vec3_add(hit.normal,
			vec3_new((i % 3) * 0.5 - 0.5, ((i / 3) % 3) * 0.5 - 0.5,
				((i / 9) % 3) * 0.5 - 0.5)));
		bounce_ray.origin = vec3_add(hit.point, vec3_scale(hit.normal,
			EPSILON * 10));
		bounce_ray.direction = sample_dir;
		bounce_hit = find_closest_hit(bounce_ray, scene);
		if (bounce_hit.hit)
			result = vec3_add(result, vec3_scale(bounce_hit.color, 0.2));
		i++;
	}
	return (vec3_scale(result, 1.0 / samples));
}
#endif

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
#ifdef ENABLE_COLOR_BLEEDING
	result = vec3_add(result, vec3_mult(hit.color,
		calculate_color_bleeding(hit, scene)));
#endif
	return (result);
}
