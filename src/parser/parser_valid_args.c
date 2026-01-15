/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/14 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

static bool	check_3arg_elements(char **elem, size_t nb, int line,
		t_error_list *err)
{
	size_t	len;

	len = ft_strlen(elem[0]);
	if (ft_strncmp(elem[0], "C", len) == 0
		|| ft_strncmp(elem[0], "pl", len) == 0
		|| ft_strncmp(elem[0], "sp", len) == 0
		|| ft_strncmp(elem[0], "plc", len) == 0)
	{
		if (nb == 3)
			return (true);
		else
			return (error_list_add(err, line, "Expected 3 args.", elem[0]),
				false);
	}
	return (false);
}

static bool	check_other_elements(char **elem, size_t nb, int line,
		t_error_list *err)
{
	size_t	len;

	len = ft_strlen(elem[0]);
	if (ft_strncmp(elem[0], "L", len) == 0 && (nb == 2 || nb == 3))
		return (true);
	if (ft_strncmp(elem[0], "L", len) == 0)
		return (error_list_add(err, line, "Expected 2-3 args.", elem[0]),
			false);
	if (ft_strncmp(elem[0], "A", len) == 0 && nb == 2)
		return (true);
	if (ft_strncmp(elem[0], "A", len) == 0)
		return (error_list_add(err, line, "Expected 2 args.", elem[0]), false);
	if ((ft_strncmp(elem[0], "cy", len) == 0
			|| ft_strncmp(elem[0], "co", len) == 0) && nb == 5)
		return (true);
	if (ft_strncmp(elem[0], "cy", len) == 0
		|| ft_strncmp(elem[0], "co", len) == 0)
		return (error_list_add(err, line, "Expected 5 args.", elem[0]), false);
	if (ft_strncmp(elem[0], "spt", len) == 0 && (nb == 4 || nb == 5))
		return (true);
	if (ft_strncmp(elem[0], "spt", len) == 0)
		return (error_list_add(err, line, "Expected 4-5 args.", elem[0]),
			false);
	return (error_list_add(err, line, "Unknown element.", elem[0]), false);
}

bool	correct_number_of_elements(char **elem, int line, t_error_list *err)
{
	size_t	nb_args;

	if (!elem || !elem[0])
		return (error_list_add(err, line, "Empty line.", NULL), false);
	nb_args = double_array_len(elem + 1);
	if (check_3arg_elements(elem, nb_args, line, err))
		return (true);
	return (check_other_elements(elem, nb_args, line, err));
}
