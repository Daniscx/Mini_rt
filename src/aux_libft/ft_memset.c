/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:58:17 by dmaestro          #+#    #+#             */
/*   Updated: 2024/09/17 19:58:24 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	dest = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		dest[i] = c;
		i++;
	}
	return (dest);
}
