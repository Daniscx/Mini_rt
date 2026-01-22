/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 17:14:48 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/parser_internal.h"

static int	parse_sphere_diameter(char **elem, t_list **res, int l,
		t_error_list *e)
{
	t_float_ctx	ctx;

	ctx = (t_float_ctx){0, 0, false, l, e, "diameter"};
	return (add_float_value(res, elem[2], &ctx));
}

static int	parse_sphere_textures(char **elem, t_list **res, int l,
		t_error_list *e)
{
	char	*texture;

	if (!elem[4])
		return (0);
	texture = parser_texture_name(elem[4]);
	if (texture == NULL)
		return (error_list_add(e, l, "Texture fail.", "texture"), -1);
	ft_lstadd_back(res, ft_lstnew(texture));
	if (!elem[5])
		return (0);
	texture = parser_texture_name(elem[5]);
	if (texture == NULL)
		return (error_list_add(e, l, "Bump fail.", "normal_map"), -1);
	ft_lstadd_back(res, ft_lstnew(texture));
	return (0);
}

static t_list	**parse_sphere_color(char **elem, t_list **res, int line,
		t_error_list *e)
{
	char		**split;
	t_list		**float_list;
	t_float_ctx	ctx;

	split = ft_split(elem[3], ',');
	ctx = (t_float_ctx){255, 0, true, line, e, "color"};
	float_list = list_of_float_checker(split, &ctx);
	free_double_pointer(split);
	if (!float_list)
		return (primitive_sphere_destructor(res), NULL);
	ft_lstadd_back(res, ft_lstnew(float_list));
	if (parse_sphere_textures(elem, res, line, e) == -1)
		return (primitive_sphere_destructor(res), NULL);
	return (res);
}

t_list	**sphere_parser(char **elem, int line, t_error_list *e)
{
	t_list		**result;
	t_list		**float_list;
	char		**split;
	t_float_ctx	ctx;

	result = ft_calloc(1, sizeof(t_list *));
	ft_lstadd_back(result, ft_lstnew(ft_strdup(elem[0])));
	split = ft_split(elem[1], ',');
	ctx = (t_float_ctx){0, 0, false, line, e, "position"};
	float_list = list_of_float_checker(split, &ctx);
	free_double_pointer(split);
	if (!float_list)
		return (primitive_sphere_destructor(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	if (parse_sphere_diameter(elem, result, line, e) == -1)
		return (primitive_sphere_destructor(result), NULL);
	return (parse_sphere_color(elem, result, line, e));
}
