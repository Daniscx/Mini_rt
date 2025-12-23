/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_effects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:40:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 03:22:47 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/texture.h"
# include "../../includes/hit.h"
# include "../../includes/objects.h"

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

static t_vec3	get_bump_tangent(t_vec3 normal)
{
	t_vec3	tangent;

	tangent = vec3_normalize(vec3_cross(normal, vec3_new(0, 1, 0)));
	if (vec3_length(tangent) < EPSILON)
		tangent = vec3_normalize(vec3_cross(normal, vec3_new(1, 0, 0)));
	return (tangent);
}

static void	calculate_bump_gradients(struct s_hit *hit, double *du, double *dv)
{
	t_vec3	color_c;
	t_vec3	color_u;
	t_vec3	color_v;
	double	delta;

	delta = 0.001;
	color_c = texture_sample(hit->bump_map, hit->u, hit->v);
	color_u = texture_sample(hit->bump_map, hit->u + delta, hit->v);
	color_v = texture_sample(hit->bump_map, hit->u, hit->v + delta);
	*du = (color_u.x + color_u.y + color_u.z)
		/ 3.0 - (color_c.x + color_c.y + color_c.z) / 3.0;
	*dv = (color_v.x + color_v.y + color_v.z)
		/ 3.0 - (color_c.x + color_c.y + color_c.z) / 3.0;
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
	calculate_bump_gradients(hit, &du, &dv);
	tangent = get_bump_tangent(hit->normal);
	bitangent = vec3_cross(hit->normal, tangent);
	perturbed = vec3_add(hit->normal,
			vec3_scale(tangent, -du * BUMP_STRENGTH * 10.0));
	perturbed = vec3_add(perturbed,
			vec3_scale(bitangent, -dv * BUMP_STRENGTH * 10.0));
	return (vec3_normalize(perturbed));
}
