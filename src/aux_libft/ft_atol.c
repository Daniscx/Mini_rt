/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:07:47 by dmaestro          #+#    #+#             */
/*   Updated: 2025/03/12 16:50:20 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atol(const char *nptr)
{
	long long	nb;
	int			i;
	int			t;

	nb = 0;
	i = 0;
	t = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			t = -t;
		i++;
	}
	while ((nptr[i] <= '9' && nptr[i] >= '0'))
	{
		nb = ((nb * 10) + nptr[i] - '0');
		i++;
	}
	return (t * nb);
}
