/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:12:12 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/16 19:26:25 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
