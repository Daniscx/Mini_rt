/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy_caps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:45:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:10:22 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_hit	check_cap(t_ray ray, t_cylinder *cy, t_vec3 cap_center)
{
	t_hit	cap_hit;
	t_plane	cap;
	double	dist;

	cap.normal = cy->axis;
	cap.point = cap_center;
	cap.color = cy->color;
	cap_hit = intersect_plane(ray, &cap);
	if (cap_hit.hit)
	{
		dist = vec3_length(vec3_sub(cap_hit.point, cap_center));
		if (dist > cy->diameter / 2.0)
			cap_hit.hit = false;
	}
	return (cap_hit);
}

t_hit	intersect_cylinder_caps(t_ray ray, t_cylinder *cy)
{
	t_hit	hit;
	t_hit	cap_hit;
	t_vec3	top_center;

	hit = hit_new();
	cap_hit = check_cap(ray, cy, cy->center);
	if (cap_hit.hit && cap_hit.t < hit.t)
		hit = cap_hit;
	top_center = vec3_add(cy->center, vec3_scale(cy->axis, cy->height));
	cap_hit = check_cap(ray, cy, top_center);
	if (cap_hit.hit && cap_hit.t < hit.t)
		hit = cap_hit;
	return (hit);
}
