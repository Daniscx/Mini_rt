/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 17:14:48 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

static int	parse_sphere(char **elem, t_list **list, int line, t_error_list *e)
{
	t_list	**result;

	result = sphere_parser(elem, line, e);
	if (!result)
		return (-1);
	ft_lstadd_back(list, ft_lstnew(result));
	return (0);
}

static int	parse_plane(char **elem, t_list **list, int line, t_error_list *e)
{
	t_list	**result;

	result = plane_parser(elem, line, e);
	if (!result)
		return (-1);
	ft_lstadd_back(list, ft_lstnew(result));
	return (0);
}

static int	parse_cylinder(char **elem, t_list **list, int line,
		t_error_list *e)
{
	t_list	**result;

	result = cylinder_parser(elem, line, e);
	if (!result)
		return (-1);
	ft_lstadd_back(list, ft_lstnew(result));
	return (0);
}

int	object_parser(char **elem, t_list **list, int line, t_error_list *e)
{
	size_t	len;

	len = ft_strlen(elem[0]);
	if (ft_strncmp(elem[0], "sp", len) == 0
		|| ft_strncmp(elem[0], "spt", len) == 0)
		return (parse_sphere(elem, list, line, e));
	if (ft_strncmp(elem[0], "pl", len) == 0
		|| ft_strncmp(elem[0], "plc", len) == 0)
		return (parse_plane(elem, list, line, e));
	if (ft_strncmp(elem[0], "cy", len) == 0
		|| ft_strncmp(elem[0], "co", len) == 0)
		return (parse_cylinder(elem, list, line, e));
	return (0);
}
