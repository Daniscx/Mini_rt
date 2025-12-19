/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:15:09 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 15:13:13 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_printf(char const *str, ...)
{
	va_list	pf;
	size_t	t;

	t = 0;
	va_start(pf, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			t += ft_selector(pf, str);
		}
		else
			t += ft_putchar(*str);
		str++;
	}
	va_end(pf);
	return (t);
}
