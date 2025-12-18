/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexnumax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:37:55 by dmaestro          #+#    #+#             */
/*   Updated: 2024/12/18 20:16:43 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static void	ft_puthex(unsigned int pf, char *p3, int i)
{
	p3[i] = '\0';
	i--;
	while (pf >= 16)
	{
		if (pf % 16 <= 9)
			p3[i] = pf % 16 + '0';
		else
			p3[i] = pf % 16 + 'A' - 10;
		pf = pf / 16;
		i--;
	}
	if ((pf % 16) <= 9)
	{
		p3[i] = pf % 16 + '0';
		i--;
	}
	if (pf % 16 >= 10)
		p3[i] = pf % 16 + 'A' - 10;
	ft_putstr(p3);
}

static int	ft_pos(unsigned int pf)
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

int	ft_puthexnumax(unsigned int pf)
{
	int		i;
	char	*p3;

	if (pf == 0)
		return (ft_putchar('0'));
	i = ft_pos(pf);
	p3 = malloc(ft_pos(pf) + 1);
	if (!p3)
	{
		free(p3);
		return ('\0');
	}
	ft_puthex(pf, p3, i);
	free(p3);
	return (i);
}
