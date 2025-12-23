/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/parser_internal.h"
# include "../../includes/minirt.h"

t_error_list	*error_list_create(void)
{
	t_error_list	*list;

	list = ft_calloc(1, sizeof(t_error_list));
	if (!list)
		return (NULL);
	list->first = NULL;
	list->last = NULL;
	list->count = 0;
	return (list);
}

void	error_list_add(t_error_list *list, int line, char *msg, char *param)
{
	t_parse_error	*error;

	if (!list || !msg)
		return ;
	error = ft_calloc(1, sizeof(t_parse_error));
	if (!error)
		return ;
	error->line = line;
	error->message = ft_strdup(msg);
	if (param)
		error->parameter = ft_strdup(param);
	else
		error->parameter = NULL;
	error->next = NULL;
	if (!list->first)
	{
		list->first = error;
		list->last = error;
	}
	else
	{
		list->last->next = error;
		list->last = error;
	}
	list->count++;
}

void	error_list_print(t_error_list *list)
{
	t_parse_error	*current;
	char			*line_str;

	if (!list || !list->first)
		return ;
	current = list->first;
	while (current)
	{
		ft_putstr_fd("\033[1;36mminiRT: \033[1;31mError", STDERR_FILENO);
		if (current->line > 0)
		{
			ft_putstr_fd(" (Line ", STDERR_FILENO);
			line_str = ft_itoa(current->line);
			ft_putstr_fd(line_str, STDERR_FILENO);
			free(line_str);
			ft_putstr_fd(")", STDERR_FILENO);
		}
		ft_putstr_fd(": \033[0m", STDERR_FILENO);
		if (current->parameter)
		{
			ft_putstr_fd("In parameter '\033[1;33m", STDERR_FILENO);
			ft_putstr_fd(current->parameter, STDERR_FILENO);
			ft_putstr_fd("\033[0m': ", STDERR_FILENO);
		}
		ft_putendl_fd(current->message, STDERR_FILENO);
		current = current->next;
	}
}

void	error_list_free(t_error_list *list)
{
	t_parse_error	*current;
	t_parse_error	*next;

	if (!list)
		return ;
	current = list->first;
	while (current)
	{
		next = current->next;
		if (current->message)
			free(current->message);
		if (current->parameter)
			free(current->parameter);
		free(current);
		current = next;
	}
	free(list);
}
