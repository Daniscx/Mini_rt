/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:00:20 by dmaestro          #+#    #+#             */
/*   Updated: 2024/09/19 19:00:21 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*jumpei;
	size_t	i;
	size_t	j;
	size_t	len1;

	i = 0;
	j = 0;
	jumpei = (char *)src;
	while (dst[i] && i < size)
		i++;
	len1 = i;
	if (len1 == size)
		return (ft_strlen(src) + size);
	while (jumpei[j] && i < (size - 1))
	{
		dst[i] = jumpei[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (len1 + ft_strlen(src));
}
