/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:25:50 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:18:38 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"

void	object_destructor(t_object *object)
{
	t_sphere	*sp;

	if (!object)
		return ;
	if (object->figure)
	{
		if (object->identificator == Sp || object->identificator == Spt)
		{
			sp = (t_sphere *)object->figure;
			if (sp->texture)
				texture_free(sp->texture);
			if (sp->bump_map)
				texture_free(sp->bump_map);
		}
		free(object->figure);
	}
	free(object);
}

void	list_of_objects_destructor(t_list **objects)
{
	t_list		*aux;
	t_list		*temp;
	t_object	*obj;

	if (!objects || !*objects)
		return ;
	aux = *objects;
	while (aux)
	{
		obj = (t_object *)aux->content;
		object_destructor(obj);
		temp = aux;
		aux = aux->next;
		free(temp);
	}
	free(objects);
}

t_vec3	get_object_center(t_object *obj)
{
	if (!obj || !obj->figure || !obj->postion)
		return (vec3_new(0, 0, 0));
	return (obj->postion(obj->figure));
}

void	move_object(t_object *obj, t_vec3 new_center)
{
	if (!obj || !obj->figure || !obj->movement)
		return ;
	obj->movement(obj->figure, new_center);
}

void	print_list_of_objects(t_list **objects)
{
	t_list		*aux;
	t_object	*obj;
	int			index;

	index = 0;
	if (!objects || !*objects)
	{
		printf("No objects to display.\n");
		return ;
	}
	aux = *objects;
	printf("List of Objects:\n");
	while (aux)
	{
		obj = (t_object *)aux->content;
		printf("Object %d: type=%d\n", index, obj->identificator);
		aux = aux->next;
		index++;
	}
}
