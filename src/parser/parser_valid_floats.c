/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_floats.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/14 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

static bool	check_float_str(char *str, t_float_ctx *ctx)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '.')
		{
			error_list_add(ctx->errors, ctx->line, "Invalid num.", ctx->param);
			return (false);
		}
		i++;
	}
	return (true);
}

static t_list	**init_float_list(char **split, t_float_ctx *ctx)
{
	if (double_array_len(split) != 3)
	{
		error_list_add(ctx->errors, ctx->line, "Expected 3 vals.", ctx->param);
		return (NULL);
	}
	return (ft_calloc(1, sizeof(t_list *)));
}

static int	add_float_value(t_list **res, char *str, t_float_ctx *ctx)
{
	float	*val;

	if (!check_float_str(str, ctx))
		return (-1);
	val = ft_calloc(1, sizeof(float));
	*val = ft_atof(str);
	if (if_betwen_values(*val, ctx->min, ctx->max) == false && ctx->range)
	{
		error_list_add(ctx->errors, ctx->line, "Out of range.", ctx->param);
		free(val);
		return (-1);
	}
	ft_lstadd_back(res, ft_lstnew(val));
	return (0);
}

t_list	**list_of_float_checker(char **split, t_float_ctx *ctx)
{
	t_list	**result;
	int		j;

	result = init_float_list(split, ctx);
	if (!result)
		return (NULL);
	j = 0;
	while (split[j])
	{
		if (add_float_value(result, split[j], ctx) == -1)
			return (free_list_of_floats(result), NULL);
		j++;
	}
	return (result);
}
