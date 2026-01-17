/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:37:23 by dmaestro          #+#    #+#             */
/*   Updated: 2026/01/17 14:22:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/light.h"
#include "../../includes/escene.h"

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

static bool	is_in_shadow(t_vec3 pt, t_vec3 n, t_vec3 l_dir, t_scene *scene)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.origin = vec3_add(pt, vec3_scale(n, EPSILON * 10));
	shadow_ray.direction = l_dir;
	hit = find_closest_hit(shadow_ray, scene);
	if (hit.hit && hit.t < l_dir.ldt_norminette)
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
	light_dir.ldt_norminette = vec3_length(light_dir);
	light_dist = light_dir.ldt_norminette;
	light_dir = vec3_normalize(light_dir);
	light_dir.ldt_norminette = light_dist;
	if (is_in_shadow(hit.point, hit.normal, light_dir, scene))
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
	t_list	*aux;
	t_light	*actual_light;

	apply_hit_effects(&hit);
	ambient = vec3_mult(hit.color, scene->al->color);
	ambient = vec3_scale(ambient, scene->al->ratio);
	result = ambient;
	aux = *scene->light;
	while (aux)
	{
		actual_light = aux->content;
		result = vec3_add(result, calculate_diffuse(hit, actual_light, scene));
		result = vec3_add(result, calculate_specular(hit, actual_light,
					view_dir));
		aux = aux->next;
	}
	if (COLOR_BLEEDING == 1)
		result = vec3_add(result, vec3_mult(hit.color,
					calculate_color_bleeding(hit, scene)));
	return (result);
}
