/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/14 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/parser_internal.h"

static int	parse_cam_fov(char **elem, t_list **list, int line, t_error_list *e)
{
	t_float_ctx	ctx;

	ctx = (t_float_ctx){180, 0, true, line, e, "FOV"};
	if (add_float_value(list, elem[3], &ctx) == -1)
		return (-1);
	return (0);
}

static int	parse_cam_vectors(char **elem, t_list **list, int line,
		t_error_list *e)
{
	char		**xyz;
	t_list		**list_float;
	t_float_ctx	ctx;

	xyz = ft_split(elem[1], ',');
	ctx = (t_float_ctx){0, 0, false, line, e, "pos"};
	list_float = list_of_float_checker(xyz, &ctx);
	free_double_pointer(xyz);
	if (!list_float)
		return (-1);
	ft_lstadd_back(list, ft_lstnew(list_float));
	xyz = ft_split(elem[2], ',');
	ctx = (t_float_ctx){0, 0, false, line, e, "orient"};
	list_float = list_of_float_checker(xyz, &ctx);
	free_double_pointer(xyz);
	if (!list_float)
		return (-1);
	ft_lstadd_back(list, ft_lstnew(list_float));
	return (0);
}

int	camera_parser(char **elem, t_list **list, int line, t_error_list *e)
{
	if (ft_strncmp(elem[0], "C", ft_strlen(elem[0])) == 0 && *list)
		return (error_list_add(e, line, "Multiple camera.", "C"), -1);
	else if (ft_strncmp(elem[0], "C", ft_strlen(elem[0])) != 0)
		return (0);
	if (parse_cam_vectors(elem, list, line, e) == -1)
		return (-1);
	return (parse_cam_fov(elem, list, line, e));
}
