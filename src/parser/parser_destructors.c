/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destructors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:16:46 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

void	free_list_of_floats(t_list **list)
{
	t_list	*actual_node;
	t_list	*aux_node;

	if (!list)
		return ;
	if (*list == NULL)
		return (free(list));
	actual_node = *list;
	while (actual_node)
	{
		aux_node = actual_node->next;
		if (actual_node->content)
			free(actual_node->content);
		free(actual_node);
		actual_node = aux_node;
	}
	if (list)
		free(list);
}

void	free_al_primitive(t_list **list)
{
	t_list	*actual_node;
	t_list	*aux_node;
	t_list	**actual_list;

	if (!list)
		return ;
	if (*list == NULL)
		return (free(list));
	actual_node = *list;
	if (actual_node->content)
		free(actual_node->content);
	aux_node = actual_node->next;
	if (aux_node)
	{
		actual_list = (t_list **)aux_node->content;
		free_list_of_floats(actual_list);
		free(aux_node);
	}
	free(actual_node);
	free(list);
}

void	free_primitive_light(t_list **list)
{
	t_list	*node;
	t_list	*next;
	int		idx;

	if (!list)
		return ;
	if (*list == NULL)
		return (free(list));
	node = *list;
	idx = 0;
	while (node)
	{
		next = node->next;
		if (node->content)
		{
			if (idx == 0 || idx == 2)
				free_list_of_floats((t_list **)node->content);
			else
				free(node->content);
		}
		free(node);
		node = next;
		idx++;
	}
	free(list);
}

void	free_list_of_lights_primitive(t_list **list)
{
	t_list	*actual_node;
	t_list	*aux_node;
	t_list	**actual_list;

	if (!list)
		return ;
	if (*list == NULL)
		return (free(list));
	actual_node = *list;
	while (actual_node)
	{
		aux_node = actual_node->next;
		actual_list = (t_list **)actual_node->content;
		free_primitive_light(actual_list);
		free(actual_node);
		actual_node = aux_node;
	}
	free(list);
}

void	free_list_camera_primitive(t_list **list)
{
	t_list	*node;
	t_list	*next;
	int		idx;

	if (!list)
		return ;
	if (*list == NULL)
		return (free(list));
	node = *list;
	idx = 0;
	while (node)
	{
		next = node->next;
		if (node->content)
		{
			if (idx == 0 || idx == 1)
				free_list_of_floats((t_list **)node->content);
			else
				free(node->content);
		}
		free(node);
		node = next;
		idx++;
	}
	free(list);
}
