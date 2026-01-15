/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_effects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:40:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/24 01:14:30 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/texture.h"
#include "../../includes/hit.h"
#include "../../includes/objects.h"

static t_vec3	get_bump_tangent(t_vec3 normal)
{
	t_vec3	tangent;

	tangent = vec3_normalize(vec3_cross(normal, vec3_new(0, 1, 0)));
	if (vec3_length(tangent) < EPSILON)
		tangent = vec3_normalize(vec3_cross(normal, vec3_new(1, 0, 0)));
	return (tangent);
}

static double	get_color_avg(t_vec3 c)
{
	return ((c.x + c.y + c.z) / 3.0);
}

static void	calc_bump_grad(struct s_hit *hit, double *du, double *dv)
{
	t_vec3	color_c;
	t_vec3	color_u;
	t_vec3	color_v;
	double	delta;

	delta = 0.001;
	color_c = texture_sample(hit->bump_map, hit->u, hit->v);
	color_u = texture_sample(hit->bump_map, hit->u + delta, hit->v);
	color_v = texture_sample(hit->bump_map, hit->u, hit->v + delta);
	*du = get_color_avg(color_u) - get_color_avg(color_c);
	*dv = get_color_avg(color_v) - get_color_avg(color_c);
}

t_vec3	apply_bump_map(struct s_hit *hit)
{
	double	du;
	double	dv;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	perturbed;

	if (!hit->bump_map)
		return (hit->normal);
	calc_bump_grad(hit, &du, &dv);
	tangent = get_bump_tangent(hit->normal);
	bitangent = vec3_cross(hit->normal, tangent);
	perturbed = vec3_add(hit->normal,
			vec3_scale(tangent, -du * BUMP_STRENGTH * 10.0));
	perturbed = vec3_add(perturbed,
			vec3_scale(bitangent, -dv * BUMP_STRENGTH * 10.0));
	return (vec3_normalize(perturbed));
}
