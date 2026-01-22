/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj_cyl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 17:14:48 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/parser_internal.h"

static int	parse_cyl_float(char *str, t_list **res, int l, t_error_list *e)
{
	t_float_ctx	ctx;

	ctx = (t_float_ctx){0, 0, false, l, e, "diam/height"};
	return (add_float_value(res, str, &ctx));
}

static int	parse_cyl_vectors(char **elem, t_list **res, int l, t_error_list *e)
{
	t_list		**float_list;
	char		**split;
	t_float_ctx	ctx;

	ft_lstadd_back(res, ft_lstnew(ft_strdup(elem[0])));
	split = ft_split(elem[1], ',');
	ctx = (t_float_ctx){0, 0, false, l, e, "position"};
	float_list = list_of_float_checker(split, &ctx);
	free_double_pointer(split);
	if (!float_list)
		return (-1);
	ft_lstadd_back(res, ft_lstnew(float_list));
	split = ft_split(elem[2], ',');
	ctx = (t_float_ctx){0, 0, false, l, e, "axis"};
	float_list = list_of_float_checker(split, &ctx);
	free_double_pointer(split);
	if (!float_list)
		return (-1);
	ft_lstadd_back(res, ft_lstnew(float_list));
	return (0);
}

t_list	**cylinder_parser(char **elem, int line, t_error_list *e)
{
	t_list		**result;
	t_list		**float_list;
	char		**split;
	t_float_ctx	ctx;

	result = ft_calloc(1, sizeof(t_list *));
	if (parse_cyl_vectors(elem, result, line, e) == -1)
		return (primitive_cylinder_destructor(result), NULL);
	if (parse_cyl_float(elem[3], result, line, e) == -1)
		return (primitive_cylinder_destructor(result), NULL);
	if (parse_cyl_float(elem[4], result, line, e) == -1)
		return (primitive_cylinder_destructor(result), NULL);
	split = ft_split(elem[5], ',');
	ctx = (t_float_ctx){255, 0, true, line, e, "color"};
	float_list = list_of_float_checker(split, &ctx);
	free_double_pointer(split);
	if (!float_list)
		return (primitive_cylinder_destructor(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	return (result);
}
