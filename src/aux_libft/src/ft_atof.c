/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:44:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/20 03:08:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static float	ft_atof_decimal(char *number, int i, float result, float sign)
{
	float	decimal;

	decimal = 0.1f;
	i++;
	while (ft_isdigit(number[i]) && number[i])
	{
		result += (number[i] - '0') * decimal;
		decimal = decimal * 0.1f;
		i++;
	}
	return (result * sign);
}

float	ft_atof(char *number)
{
	float	result;
	int		i;
	float	sign;

	i = 0;
	result = 0.000000;
	sign = 1;
	if (number[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(number[i]) && number[i])
	{
		result = result * 10.0f;
		result += number[i] - '0';
		i++;
	}
	if (number[i] != '.')
		return (result * sign);
	return (ft_atof_decimal(number, i, result, sign));
}
