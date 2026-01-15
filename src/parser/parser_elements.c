/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 17:14:48 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

static int	check_ratio_numeric(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '.')
			return (-1);
		i++;
	}
	return (0);
}

static int	parse_al_ratio(char **elem, t_list **list, int line,
		t_error_list *e)
{
	float		*actual_float;
	char		**rgb;
	t_list		**list_float;
	t_float_ctx	ctx;

	if (check_ratio_numeric(elem[1]) == -1)
		return (error_list_add(e, line, "Invalid num.", "ratio"), -1);
	actual_float = ft_calloc(1, sizeof(float));
	*actual_float = ft_atof(elem[1]);
	if (if_betwen_values(*actual_float, 0, 1) == false)
		return (free(actual_float), error_list_add(e, line,
				"Value 0.0-1.0.", "ratio"), -1);
	ft_lstadd_back(list, ft_lstnew(actual_float));
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
