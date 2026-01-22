/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2026/01/22 16:50:04 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/parser_internal.h"

static int	parse_light_brightness(char **elem, t_list **new_l, int l,
		t_error_list *e)
{
	t_float_ctx	ctx;

	ctx = (t_float_ctx){1, 0, true, l, e, "brightness"};
	if (add_float_value(new_l, elem[2], &ctx) == -1)
	{
		free_primitive_light(new_l);
		return (-1);
	}
	return (0);
}

static char	*get_default_color(char **elem)
{
	char	*default_color;

	default_color = NULL;
	if (!elem[3])
	{
		default_color = ft_strdup("255,255,255");
		elem[3] = default_color;
	}
	return (default_color);
}

static int	parse_light_color(char **elem, t_list **new_l, int l,
		t_error_list *e)
{
	char		**split;
	t_list		**list_float;
	char		*default_color;
	t_float_ctx	ctx;

	default_color = get_default_color(elem);
	split = ft_split(elem[3], ',');
	if (!split || *split == NULL)
	{
		free_primitive_light(new_l);
		error_list_add(e, l, "Invalid color.", "color");
		return (free(default_color), -1);
	}
	ctx = (t_float_ctx){255, 0, true, l, e, "color"};
	list_float = list_of_float_checker(split, &ctx);
	free_double_pointer(split);
	if (!list_float)
	{
		free_primitive_light(new_l);
		return (free(default_color), -1);
	}
	ft_lstadd_back(new_l, ft_lstnew(list_float));
	return (free(default_color), 0);
}

int	light_parser(char **elem, t_list **list, int line, t_error_list *e)
{
	t_list		**new_light;
	t_list		**list_float;
	char		**split;
	t_float_ctx	ctx;

	if (ft_strncmp(elem[0], "L", ft_strlen(elem[1])))
		return (0);
	new_light = ft_calloc(1, sizeof(t_list *));
	split = ft_split(elem[1], ',');
	if (!split || *split == NULL)
		return (error_list_add(e, line, "Invalid pos.", "position"),
			free(new_light), -1);
	ctx = (t_float_ctx){0, 0, false, line, e, "position"};
	list_float = list_of_float_checker(split, &ctx);
	free_double_pointer(split);
	if (!list_float)
		return (free(new_light), -1);
	ft_lstadd_front(new_light, ft_lstnew(list_float));
	if (parse_light_brightness(elem, new_light, line, e) == -1)
		return (-1);
	if (parse_light_color(elem, new_light, line, e) == -1)
		return (-1);
	ft_lstadd_back(list, ft_lstnew(new_light));
	return (0);
}
