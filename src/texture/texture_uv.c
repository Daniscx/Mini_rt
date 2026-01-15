/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_uv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/14 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/texture.h"
#include "../../includes/hit.h"
#include "../../includes/objects.h"

void	sphere_get_uv(t_vec3 point, t_vec3 center, double *u, double *v)
{
	t_vec3	local;
	double	theta;
	double	phi;

	local = vec3_normalize(vec3_sub(point, center));
	theta = atan2(local.x, local.z);
	phi = asin(local.y);
	*u = 1.0 - (theta + M_PI) / (2.0 * M_PI);
	*v = (phi + M_PI / 2.0) / M_PI;
}

t_vec3	apply_texture(struct s_hit *hit)
{
	if (!hit->texture)
		return (hit->color);
	return (texture_sample(hit->texture, hit->u, hit->v));
}
