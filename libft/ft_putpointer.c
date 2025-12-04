/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:52:29 by dmaestro          #+#    #+#             */
/*   Updated: 2024/12/18 19:27:13 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pos(unsigned long pf)
{
	int	i;

	i = 0;
	while (pf > 0)
	{
		pf = pf / 16;
		i++;
	}
	return (i);
}

static void	ft_puthex(unsigned long pf, char *p3, int i)
{
	p3[i] = '\0';
	i--;
	while (pf >= 16)
	{
		if (pf % 16 <= 9)
			p3[i] = pf % 16 + '0';
		else
			p3[i] = pf % 16 + 'a' - 10;
		pf = pf / 16;
		i--;
	}
	if (pf % 16 <= 9)
	{
		p3[i] = pf % 16 + '0';
		i--;
	}
	if (pf % 16 >= 10)
		p3[i] = pf % 16 + 'a' - 10;
	ft_putstr(p3);
}

int	ft_putpointer(void *pf)
{
	unsigned long	p2;
	int				i;
	char			*p3;

	if (!pf)
		return (ft_putstr("(nil)"));
	p2 = (unsigned long)pf;
	i = ft_pos(p2);
	p3 = (char *)malloc(ft_pos(p2) + 3);
	if (!p3)
	{
		free(p3);
		return ('\0');
	}
	p3[0] = '0';
	p3[1] = 'x';
	ft_puthex(p2, p3, i + 2);
	free(p3);
	return (i + 2);
}
