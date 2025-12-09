/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:12:12 by dmaestro          #+#    #+#             */
/*   Updated: 2024/09/19 20:12:14 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*car;
	unsigned char	*whacala;
	int				w;

	whacala = (unsigned char *)dest;
	car = (unsigned char *)src;
	w = 0;
	if (!src && !dest)
		return (NULL);
	if (dest < src)
	{
		while ((size_t)w < n)
		{
			whacala[w] = car[w];
			w++;
		}
		return (whacala);
	}
	w = n;
	while (w != 0)
	{
		whacala[w - 1] = car[w - 1];
		w--;
	}
	return (whacala);
}
