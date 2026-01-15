/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 02:39:47 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:47 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hit.h"
#include "../../includes/texture.h"
#include "../../includes/escene.h"

t_hit	hit_new(void)
{
	t_hit	hit;

	hit.hit = false;
	hit.t = INFINITY;
	hit.point = vec3_new(0, 0, 0);
	hit.normal = vec3_new(0, 1, 0);
	hit.color = vec3_new(0, 0, 0);
	hit.specular = 1.0;
	hit.u = 0;
	hit.v = 0;
	hit.texture = NULL;
	hit.bump_map = NULL;
	hit.checkerboard = false;
	return (hit);
}

static t_hit	check_object_hit(t_object *obj, t_ray ray, t_hit closest)
{
	t_hit	current;

	if (obj && obj->intersecction && obj->figure)
	{
		current = obj->intersecction(ray, obj->figure);
		if (current.hit && current.t < closest.t)
		{
			closest = current;
			closest.checkerboard = obj->check_board;
		}
	}
	return (closest);
}

t_hit	find_closest_hit(t_ray ray, t_scene *scene)
{
	t_hit		closest;
	t_list		*aux;
	t_object	*current_object;

	closest = hit_new();
	if (!scene || !scene->object)
		return (closest);
	aux = *scene->object;
	while (aux)
	{
		current_object = aux->content;
		closest = check_object_hit(current_object, ray, closest);
		aux = aux->next;
	}
	return (closest);
}

void	apply_hit_effects(t_hit *hit)
{
	if (hit->bump_map)
		hit->normal = apply_bump_map(hit);
	if (hit->texture)
		hit->color = apply_texture(hit);
	if (hit->checkerboard)
		hit->color = apply_checkerboard(hit);
}
