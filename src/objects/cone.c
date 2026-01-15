/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 05:42:53 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:20:01 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"

static t_vec3	get_cone_center(void *cone)
{
	t_cone	*co;
	t_vec3	offset;

	co = (t_cone *)cone;
	offset = vec3_scale(co->axis, co->height / 2.0);
	return (vec3_add(co->apex, offset));
}

void	move_cone(void *co, t_vec3 new_center)
{
	t_cone	*cone;
	t_vec3	offset;

	cone = (t_cone *)co;
	offset = vec3_scale(cone->axis, cone->height / 2.0);
	cone->apex = vec3_sub(new_center, offset);
}

static bool	collides_cone(t_vec3 pos, void *cone)
{
	t_cone	*co;
	t_vec3	to_pos;
	double	proj;
	double	cone_radius;
	double	dist;

	co = (t_cone *)cone;
	to_pos = vec3_sub(pos, co->apex);
	proj = vec3_dot(to_pos, co->axis);
	if (proj < -CAMERA_RADIUS || proj > co->height + CAMERA_RADIUS)
		return (false);
	if (co->height - proj < 0)
		cone_radius = 0;
	else if (co->height - proj > co->height)
		cone_radius = co->height * tan(co->angle * M_PI / 180.0);
	else
		cone_radius = (co->height - proj) * tan(co->angle * M_PI / 180.0);
	dist = vec3_length(vec3_sub(pos, vec3_add(co->apex,
					vec3_scale(co->axis, proj))));
	return (dist < cone_radius + CAMERA_RADIUS);
}

t_cone	*cone_constructor(t_list **components, t_object *object)
{
	t_cone	*result;
	t_list	*aux;

	aux = *(components);
	result = ft_calloc(1, sizeof(t_cone));
	result->apex = vector_constructor(aux->content, false);
	aux = aux->next;
	result->axis = vec3_normalize(vector_constructor(aux->content, false));
	aux = aux->next;
	result->angle = *(float *)aux->content;
	aux = aux->next;
	result->height = *(float *)aux->content;
	aux = aux->next;
	result->color = vector_constructor(aux->content, true);
	object->check_board = false;
	object->intersecction = intersect_cone;
	object->postion = get_cone_center;
	object->movement = move_cone;
	object->collision = collides_cone;
	return (result);
}

void	cone_print(t_cone *co)
{
	printf("Cone:\n");
	printf(" Apex: (%f, %f, %f)\n", co->apex.x, co->apex.y, co->apex.z);
	printf(" Axis: (%f, %f, %f)\n", co->axis.x, co->axis.y, co->axis.z);
	printf(" Angle: %f\n", co->angle);
	printf(" Height: %f\n", co->height);
	printf(" Color: (%f, %f, %f)\n", co->color.x, co->color.y, co->color.z);
}
