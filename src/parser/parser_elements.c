/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2026/01/22 17:00:04 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/parser_internal.h"

static int	parse_al_ratio(char **elem, t_list **list, int line,
		t_error_list *e)
{
	char		**rgb;
	t_list		**list_float;
	t_float_ctx	ctx;

	ctx = (t_float_ctx){1, 0, true, line, e, "ratio"};
	if (add_float_value(list, elem[1], &ctx) == -1)
		return (-1);
	rgb = ft_split(elem[2], ',');
	ctx = (t_float_ctx){255, 0, true, line, e, "color"};
	list_float = list_of_float_checker(rgb, &ctx);
	free_double_pointer(rgb);
	if (!list_float)
		return (-1);
	return (ft_lstadd_back(list, ft_lstnew(list_float)), 0);
}

int	ambient_light_parser(char **elem, t_list **list, int line, t_error_list *e)
{
	if (ft_strncmp(elem[0], "A", ft_strlen(elem[0])) == 0 && *list)
		return (error_list_add(e, line, "Multiple ambient.", "A"), -1);
	else if (ft_strncmp(elem[0], "A", ft_strlen(elem[0])) != 0)
		return (0);
	return (parse_al_ratio(elem, list, line, e));
}
