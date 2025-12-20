/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:19:30 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/20 03:08:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_count(int i)
{
	int	n;

	n = 0;
	if (i < 0)
		n++;
	while (i < -9 || i > 9)
	{
		i = i / 10;
		n++;
	}
	return (n + 1);
}

static void	ft_trueputnb(int i)
{
	if (i == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (i < 0)
		{
			i = -i;
			ft_putchar('-');
		}
		if (i > 9)
			ft_putnb(i / 10);
		ft_putchar(i % 10 + '0');
	}
}

int	ft_putnb(int i)
{
	ft_trueputnb(i);
	return (ft_count(i));
}
