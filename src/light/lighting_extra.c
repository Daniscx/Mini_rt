/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:35:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:10:51 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	apply_hit_effects(t_hit *hit)
{
	if (hit->bump_map)
		hit->normal = apply_bump_map(hit);
	if (hit->texture)
		hit->color = apply_texture(hit);
	if (hit->checkerboard)
		hit->color = apply_checkerboard(hit);
}

static t_vec3	get_sample_direction(t_vec3 normal, int i)
{
	t_vec3	offset;

	offset.x = (i % 3) * 0.5 - 0.5;
	offset.y = ((i / 3) % 3) * 0.5 - 0.5;
	offset.z = ((i / 9) % 3) * 0.5 - 0.5;
	return (vec3_normalize(vec3_add(normal, offset)));
}

static t_vec3	trace_bounce(t_hit hit, t_scene *scene, int i)
{
	t_ray	bounce_ray;
	t_hit	bounce_hit;
	t_vec3	sample_dir;

	sample_dir = get_sample_direction(hit.normal, i);
	bounce_ray.origin = vec3_add(hit.point, vec3_scale(hit.normal, EPSILON * 10));
	bounce_ray.direction = sample_dir;
	bounce_hit = find_closest_hit(bounce_ray, scene);
	if (bounce_hit.hit)
		return (vec3_scale(bounce_hit.color, 0.2));
	return (vec3_new(0, 0, 0));
}

t_vec3	calculate_color_bleeding(t_hit hit, t_scene *scene)
{
	t_vec3	result;
	int		samples;
	int		i;

	result = vec3_new(0, 0, 0);
	samples = 8;
	i = 0;
	while (i < samples)
	{
		result = vec3_add(result, trace_bounce(hit, scene, i));
		i++;
	}
	return (vec3_scale(result, 1.0 / samples));
}
