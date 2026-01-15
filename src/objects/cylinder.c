/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:47:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:19:27 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"

t_vec3	get_cylinder_body_center(void *cy)
{
	t_cylinder	*cylinder;
	t_vec3		offset;

	cylinder = (t_cylinder *)cy;
	offset = vec3_scale(cylinder->axis, cylinder->height / 2.0);
	return (vec3_add(cylinder->center, offset));
}

void	move_cylinder(void *cy, t_vec3 new_center)
{
	t_vec3		offset;
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)cy;
	offset = vec3_scale(cylinder->axis, cylinder->height / 2.0);
	cylinder->center = vec3_sub(new_center, offset);
}

static bool	collides_cylinder(t_vec3 pos, void *cylinder)
{
	t_vec3		to_pos;
	double		proj;
	t_vec3		closest;
	double		dist;
	t_cylinder	*cy;

	cy = (t_cylinder *)cylinder;
	to_pos = vec3_sub(pos, cy->center);
	proj = vec3_dot(to_pos, cy->axis);
	if (proj < -CAMERA_RADIUS || proj > cy->height + CAMERA_RADIUS)
		return (false);
	closest = vec3_add(cy->center, vec3_scale(cy->axis, proj));
	dist = vec3_length(vec3_sub(pos, closest));
	return (dist < cy->diameter / 2.0 + CAMERA_RADIUS);
}

t_cylinder	*cylinder_constructor(t_list **components, t_object *object)
{
	t_cylinder	*result;
	t_list		*aux;

	aux = *(components);
	result = ft_calloc(1, sizeof(t_cylinder));
	result->center = vector_constructor(aux->content, false);
	aux = aux->next;
	result->axis = vec3_normalize(vector_constructor(aux->content, false));
	aux = aux->next;
	result->diameter = *(float *)aux->content;
	aux = aux->next;
	result->height = *(float *)aux->content;
	aux = aux->next;
	result->color = vector_constructor(aux->content, true);
	object->intersecction = intersect_cylinder;
	object->postion = get_cylinder_body_center;
	object->movement = move_cylinder;
	object->check_board = false;
	object->collision = collides_cylinder;
	return (result);
}

void	cylinder_print(t_cylinder *cylinder)
{
	printf("Cylinder:\n");
	printf(" Center: (%.2f, %.2f, %.2f)\n",
		cylinder->center.x, cylinder->center.y, cylinder->center.z);
	printf(" Axis: (%.2f, %.2f, %.2f)\n",
		cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
	printf(" Diameter: %.2f\n", cylinder->diameter);
	printf(" Height: %.2f\n", cylinder->height);
	printf(" Color: (%.2f, %.2f, %.2f)\n",
		cylinder->color.x, cylinder->color.y, cylinder->color.z);
}
