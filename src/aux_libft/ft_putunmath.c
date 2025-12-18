/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunmath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:41:33 by dmaestro          #+#    #+#             */
/*   Updated: 2024/12/18 19:21:24 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
