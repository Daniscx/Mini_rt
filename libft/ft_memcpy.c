/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:00 by dmaestro          #+#    #+#             */
/*   Updated: 2024/09/18 17:05:06 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*desti;
	unsigned char	*srci;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	desti = dest;
	srci = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		desti[i] = srci[i];
		i++;
	}
	return ((char *)desti);
}
