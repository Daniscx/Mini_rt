/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_general.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/14 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

static t_list	**handle_error(t_list **result, t_error_list *err,
		void (*d)(t_list **))
{
	error_list_print(err);
	error_list_free(err);
	if (d && *result)
		d(result);
	else
		free(result);
	return (NULL);
}

static int	process_nodes(t_list *node, t_list **result, t_parser_func f,
		t_error_list *err)
{
	t_line_data	*ld;
	int			has_err;

	has_err = 0;
	while (node)
	{
		ld = (t_line_data *)node->content;
		if (correct_number_of_elements(ld->content, ld->line_number, err)
			== false)
			has_err = 1;
		else if (f(ld->content, result, ld->line_number, err) == -1)
			has_err = 1;
		node = node->next;
	}
	return (has_err);
}

t_list	**general_parser(t_list **list, t_parser_func f, void (*d)(t_list **))
{
	t_list			**result;
	t_error_list	*errors;
	int				has_err;

	if (!list || *list == NULL)
		return (NULL);
	result = ft_calloc(1, sizeof(t_list *));
	errors = error_list_create();
	has_err = process_nodes(*list, result, f, errors);
	if (has_err)
		return (handle_error(result, errors, d));
	error_list_free(errors);
	if (result && *result == NULL)
		return (free(result), NULL);
	return (result);
}
