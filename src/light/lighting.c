/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 19:28:26 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

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

t_vec3	calculate_lighting(t_hit hit, t_scene *scene, t_vec3 view_dir)
{
	t_vec3	result;
	t_vec3	ambient;
	int		i;

	apply_hit_effects(&hit);
	ambient = vec3_mult(hit.color, scene->ambient.color);
	ambient = vec3_scale(ambient, scene->ambient.ratio);
	result = ambient;
	i = 0;
	while (i < scene->light_count)
	{
		result = vec3_add(result, calculate_diffuse(hit,
					&scene->lights[i], scene));
		result = vec3_add(result, calculate_specular(hit,
					&scene->lights[i], view_dir));
		i++;
	}
	if (COLOR_BLEEDING == 1)
		result = vec3_add(result, vec3_mult(hit.color,
					calculate_color_bleeding(hit, scene)));
	return (result);
}
