/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destruct_scene.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/14 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

void	list_of_objects_destructor_primitive(t_list **list)
{
	t_list	*actual_node;
	t_list	*aux_node;
	t_list	**actual_list;
	t_list	*content_node;

	if (!list)
		return ;
	if (*list == NULL)
		return (free(list));
	actual_node = *list;
	while (actual_node)
	{
		aux_node = actual_node->next;
		actual_list = (t_list **)actual_node->content;
		content_node = *actual_list;
		primitive_destructor_selector(actual_list,
			(char *)content_node->content);
		free(actual_node);
		actual_node = aux_node;
	}
	free(list);
}

void	escene_primitive_destructor(t_primitive_escene *primitive)
{
	if (!primitive)
		return ;
	if (primitive->al)
		free_al_primitive(primitive->al);
	if (primitive->camera)
		free_list_camera_primitive(primitive->camera);
	if (primitive->light)
		free_list_of_lights_primitive(primitive->light);
	if (primitive->object)
		list_of_objects_destructor_primitive(primitive->object);
	free(primitive);
}
