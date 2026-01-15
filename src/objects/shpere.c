/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shpere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:49:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:18:05 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"

static bool	collides_sphere(t_vec3 pos, void *sphere)
{
	double		dist;
	double		radius;
	t_sphere	*sp;

	sp = (t_sphere *)sphere;
	dist = vec3_length(vec3_sub(pos, sp->center));
	radius = sp->diameter / 2.0;
	return (dist < radius + CAMERA_RADIUS);
}

static t_vec3	get_sphere_center(void *sp)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)sp;
	return (sphere->center);
}

static void	sphere_new_center(void *sp, t_vec3 new_point)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)sp;
	sphere->center = new_point;
}

static void	sphere_set_object(t_object *obj, t_sphere *sp, bool texture)
{
	obj->textured = texture;
	if (texture == false)
	{
		sp->texture = NULL;
		sp->bump_map = NULL;
	}
	obj->check_board = false;
	obj->intersecction = intersect_sphere;
	obj->movement = sphere_new_center;
	obj->postion = get_sphere_center;
	obj->collision = collides_sphere;
}

t_sphere	*sphere_constructor(t_list **comp, t_object *obj, bool texture)
{
	t_sphere	*result;
	t_list		*aux;

	aux = *(comp);
	result = ft_calloc(1, sizeof(t_sphere));
	result->center = vector_constructor(aux->content, false);
	aux = aux->next;
	result->diameter = *(float *)aux->content;
	aux = aux->next;
	result->color = vector_constructor(aux->content, true);
	if (texture == true)
	{
		aux = aux->next;
		result->texture = texture_load_ppm(aux->content);
		if (aux->next)
			result->bump_map = texture_load_ppm(aux->next->content);
		else
			result->bump_map = NULL;
		obj->identificator = Sp;
	}
	sphere_set_object(obj, result, texture);
	return (result);
}
