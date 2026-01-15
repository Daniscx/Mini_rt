/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:50:02 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:18:31 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"

static t_vec3	get_plane_point(void *plane)
{
	t_plane	*aux;

	aux = (t_plane *)plane;
	return (aux->point);
}

static void	move_plane(void *plane, t_vec3 new_center)
{
	t_plane	*aux;

	aux = (t_plane *)plane;
	aux->point = new_center;
}

static bool	collision_plane(t_vec3 xyz, void *plane)
{
	if (!plane)
		return (false);
	(void)xyz;
	return (false);
}

t_hit	intersect_plane(t_ray ray, void *plane)
{
	t_hit	hit;
	double	denom;
	double	t;
	t_plane	*pl;

	pl = (t_plane *)plane;
	hit = hit_new();
	denom = vec3_dot(ray.direction, pl->normal);
	if (fabs(denom) < EPSILON)
		return (hit);
	t = vec3_dot(vec3_sub(pl->point, ray.origin), pl->normal) / denom;
	if (t < EPSILON)
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = pl->normal;
	if (denom > 0)
		hit.normal = vec3_negate(hit.normal);
	hit.color = pl->color;
	hit.specular = 0.3;
	return (hit);
}

t_plane	*plane_constructor(t_list **comp, t_object *obj, bool check_board)
{
	t_plane	*result;
	t_list	*aux;

	result = ft_calloc(1, sizeof(t_plane));
	aux = *comp;
	result->point = vector_constructor(aux->content, false);
	aux = aux->next;
	result->normal = vec3_normalize(vector_constructor(aux->content, false));
	aux = aux->next;
	result->color = vector_constructor(aux->content, true);
	obj->intersecction = intersect_plane;
	obj->postion = get_plane_point;
	obj->movement = move_plane;
	obj->collision = collision_plane;
	obj->check_board = check_board;
	return (result);
}
