/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:44:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 21:19:20 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

float   ft_atof(char *number)
{
    float   result;
    float   decimal;
    int     i;
    float   sing;
    
    i = 0;
    result = 0.000000;
    decimal = 0.1f;
    sing = 1;
    if (number[i] == '-')
    {
        sing = -1;
        i++;
    }
    while (ft_isdigit(number[i]) && number[i])
    {
        result = result * 10.0f;
        result += number[i] - '0';
        i++;
    }
    if (number[i] != '.')
        return (result * sing);
    i++;
    while (ft_isdigit(number[i]) && number[i])
    {
        result += (number[i] - '0')*decimal;
        decimal = decimal * 0.1f;
        i++;
    }   
    return (result * sing);
}
