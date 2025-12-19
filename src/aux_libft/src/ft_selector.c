/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 01:44:21 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 15:12:24 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_selector(va_list pf, char const *str)
{
	if (*str == 'c')
		return (ft_putchar(va_arg(pf, int)));
	if (*str == 's')
		return (ft_putstr(va_arg(pf, char *)));
	if (*str == 'X')
		return (ft_puthexnumax(va_arg(pf, unsigned long)));
	if (*str == 'x')
		return (ft_puthexnum(va_arg(pf, unsigned long)));
	if (*str == 'd' || *str == 'i')
		return (ft_putnb(va_arg(pf, int)));
	if (*str == 'p')
		return (ft_putpointer(va_arg(pf, void *)));
	if (*str == 'u')
		return (ft_putunmath(va_arg(pf, unsigned int)));
	if (*str == '%')
		return (ft_putchar('%'));
	return ('\0');
}
