/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/15 20:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Verifica si un punto esta en sombra respecto a una luz
** Lanza un rayo desde el punto hacia la luz y verifica interseccion
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
** Calcula la componente difusa de la iluminacion (modelo Lambert)
** diffuse = color * brightness * max(0, N . L)
*/
static t_vec3	calculate_diffuse(t_hit hit, t_light *light, t_scene *scene)
{
	t_vec3	light_dir;
	double	light_dist;
	double	diff;

	light_dir = vec3_sub(light->position, hit.point);
	light_dist = vec3_length(light_dir);
	light_dir = vec3_normalize(light_dir);
	if (is_in_shadow(hit.point, light_dir, light_dist, scene))
		return (vec3_new(0, 0, 0));
	diff = vec3_dot(hit.normal, light_dir);
	if (diff < 0)
		diff = 0;
	return (vec3_scale(hit.color, diff * light->brightness));
}

/*
** Calcula el color final de un punto usando modelo de iluminacion:
** Color = Ambiente + Difuso
*/
t_vec3	calculate_lighting(t_hit hit, t_scene *scene)
{
	t_vec3	result;
	t_vec3	ambient;
	t_vec3	diffuse;
	int		i;

	ambient = vec3_mult(hit.color, scene->ambient.color);
	ambient = vec3_scale(ambient, scene->ambient.ratio);
	result = ambient;
	i = 0;
	while (i < scene->light_count)
	{
		diffuse = calculate_diffuse(hit, &scene->lights[i], scene);
		result = vec3_add(result, diffuse);
		i++;
	}
	return (result);
}
