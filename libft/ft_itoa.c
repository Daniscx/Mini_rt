/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:50:35 by dmaestro          #+#    #+#             */
/*   Updated: 2024/12/18 19:18:37 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putnbr(int n, int pos, char *p3, char nb)
{
	int	i;

	i = pos;
	if (nb == '-')
		i++;
	p3[i] = '\0';
	while (pos > 0)
	{
		i--;
		p3[i] = n % 10 + '0';
		n = n / 10;
		pos--;
	}
	return (p3);
}

static int	ft_div(int n)
{
	int	ps;

	ps = 1;
	while (9 < n || -9 > n)
	{
		n = n / 10;
		ps++;
	}
	return (ps);
}

static int	ft_isnegative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	char	*p3;
	int		ps;
	char	nb;

	nb = '+';
	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ps = ft_div(n);
	p3 = (char *)malloc(ft_isnegative(n) + ps + 1);
	if (!p3)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		nb = '-';
	}
	ft_putnbr(n, ps, p3, nb);
	if (nb == '-')
		p3[0] = nb;
	return (p3);
}
