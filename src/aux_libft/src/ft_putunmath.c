/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunmath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:41:33 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/20 03:08:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_count(unsigned int i)
{
	int	n;

	n = 0;
	while (i > 9)
	{
		i = i / 10;
		n++;
	}
	return (n + 1);
}

static void	ft_writenub(unsigned int i)
{
	if (i > 9)
		ft_writenub(i / 10);
	ft_putchar(i % 10 + '0');
}

int	ft_putunmath(unsigned int i)
{
	ft_writenub(i);
	return (ft_count(i));
}
