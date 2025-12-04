/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:44:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/03 16:42:30 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

float ft_float(char *number)
{
    float result;
    float decimal;
    int i;
    float sing;
    
    i = 0;
    result = 0.000000;
    decimal = 0.1f;
    sing = 1;
    if(number[i] == '-')
    {
        sing = -1;
        i++;
    }
    while(ft_isdigit(number[i]) && number[i])
    {
        result = result * 10.0f;
        result += number[i] - '0';
        i++;
    }
    if(number[i] != '.')
        return(result * sing);
    i++;
    while(ft_isdigit(number[i]) && number[i])
    {
        result += (number[i] - '0')*decimal;
        decimal = decimal * 0.1f;
        i++;
    }   
    return(result * sing);
}
