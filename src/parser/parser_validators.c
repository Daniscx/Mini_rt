/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:42:18 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

bool	if_betwen_values(float element, float min_val, float max_val)
{
	if (element > max_val || element < min_val)
		return (false);
	return (true);
}

size_t	double_array_len(char **doble)
{
	size_t	j;

	if (!doble || !*doble)
		return (0);
	j = 0;
	while (doble[j] != NULL)
		j++;
	return (j);
}

bool	str_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_ispace(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int	ft_ispace(char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}
