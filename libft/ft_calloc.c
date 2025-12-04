/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:47:10 by dmaestro          #+#    #+#             */
/*   Updated: 2025/03/01 00:54:09 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p1;
	size_t	s;
	size_t	i;

	s = 0;
	i = 0;
	s = nmemb * size;
	if (s >= 16711568 || s <= 0)
		return (NULL);
	p1 = malloc(s + 1);
	if (!p1)
		return (NULL);
	while (i <= s)
	{
		p1[i] = 0;
		i++;
	}
	return (p1);
}
