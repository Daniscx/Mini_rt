/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:56:32 by dmaestro          #+#    #+#             */
/*   Updated: 2024/12/18 19:20:01 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pos(unsigned int pf)
{
	int	i;

	i = 0;
	while (pf > 0)
	{
		pf = pf / 16;
		i++;
	}
	return (i + 1);
}

static void	ft_six(unsigned int pf, char *p3, int i)
{
	p3[i] = '\0';
	i--;
	while (pf >= 16 && i > 0)
	{
		if ((pf % 16 <= 9))
			p3[i] = pf % 16 + '0';
		else
			p3[i] = pf % 16 + 'a' - 10;
		pf = pf / 16;
		i--;
	}
	if ((pf % 16 <= 9))
	{
		p3[i] = pf % 16 + '0';
		i--;
	}
	if (pf % 16 >= 10)
		p3[i] = pf % 16 + 'a' - 10;
	ft_putstr(p3);
}

int	ft_puthexnum(unsigned int pf)
{
	int		i;
	char	*p3;

	if (pf == 0)
		return (ft_putchar('0'));
	i = ft_pos(pf);
	p3 = malloc(ft_pos(pf));
	if (!p3)
		return ('\0');
	ft_six(pf, p3, i - 1);
	free(p3);
	return (i - 1);
}
