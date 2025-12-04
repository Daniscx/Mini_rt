/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:54:47 by dmaestro          #+#    #+#             */
/*   Updated: 2024/09/18 19:54:51 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			l1;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	l1 = 0;
	if (n == 0)
		return (0);
	while (l1 < n)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		l1++;
		str1++;
		str2++;
	}
	return (0);
}
