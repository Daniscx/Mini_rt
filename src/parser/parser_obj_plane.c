/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 17:14:48 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

static t_list	**parse_plane_vector(char *str, t_float_ctx *ctx)
{
	char	**split;
	t_list	**float_list;

	split = ft_split(str, ',');
	float_list = list_of_float_checker(split, ctx);
	free_double_pointer(split);
	return (float_list);
}

t_list	**plane_parser(char **elem, int line, t_error_list *e)
{
	t_list		**result;
	t_list		**float_list;
	t_float_ctx	ctx;

	result = ft_calloc(1, sizeof(t_list *));
	ft_lstadd_back(result, ft_lstnew(ft_strdup(elem[0])));
	ctx = (t_float_ctx){0, 0, false, line, e, "position"};
	float_list = parse_plane_vector(elem[1], &ctx);
	if (!float_list)
		return (primitive_plane_destructor(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	ctx = (t_float_ctx){1, -1, true, line, e, "normal"};
	float_list = parse_plane_vector(elem[2], &ctx);
	if (!float_list)
		return (primitive_plane_destructor(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	ctx = (t_float_ctx){255, 0, true, line, e, "color"};
	float_list = parse_plane_vector(elem[3], &ctx);
	if (!float_list)
		return (primitive_plane_destructor(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	return (result);
}
