/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destruct_primitives.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/14 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

void	primitive_sphere_destructor(t_list **list)
{
	t_list	*node;
	t_list	*next;
	int		idx;

	if (!list || *list == NULL)
		return ;
	node = *list;
	idx = 0;
	while (node)
	{
		next = node->next;
		if (node->content)
		{
			if (idx == 1 || idx == 3)
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

void	primitive_plane_destructor(t_list **list)
{
	t_list	*node;
	t_list	*next;
	int		idx;

	if (!list || *list == NULL)
		return ;
	node = *list;
	idx = 0;
	while (node)
	{
		next = node->next;
		if (node->content)
		{
			if (idx == 1 || idx == 2 || idx == 3)
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

void	primitive_cylinder_destructor(t_list **list)
{
	t_list	*node;
	t_list	*next;
	int		idx;

	if (!list || *list == NULL)
		return ;
	node = *list;
	idx = 0;
	while (node)
	{
		next = node->next;
		if (node->content)
		{
			if (idx == 1 || idx == 2 || idx == 5)
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

void	primitive_destructor_selector(t_list **list, char *identificator)
{
	size_t	len;

	len = ft_strlen(identificator);
	if (ft_strncmp(identificator, "cy", len) == 0
		|| ft_strncmp(identificator, "co", len) == 0)
		primitive_cylinder_destructor(list);
	else if (ft_strncmp(identificator, "sp", 2) == 0
		|| ft_strncmp(identificator, "spt", 3) == 0)
		primitive_sphere_destructor(list);
	else if (ft_strncmp(identificator, "pl", 2) == 0
		|| ft_strncmp(identificator, "plc", 3) == 0)
		primitive_plane_destructor(list);
}
