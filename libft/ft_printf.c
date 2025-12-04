/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:15:09 by dmaestro          #+#    #+#             */
/*   Updated: 2024/12/18 20:17:27 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
