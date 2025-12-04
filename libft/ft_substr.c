/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:25:20 by dmaestro          #+#    #+#             */
/*   Updated: 2024/09/23 18:25:22 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p2;
	size_t	i;

	i = 0;
	if (ft_strlen(s) <= start)
		return ((char *)ft_calloc(1, 1));
	if ((ft_strlen(s) - start) < len)
		p2 = malloc(ft_strlen(s) - start + 1);
	else
		p2 = malloc(len + 1);
	if (!p2)
		return (NULL);
	while (s[start] && i < len)
	{
		p2[i] = s[start];
		i++;
		start++;
	}
	p2[i] = '\0';
	return (p2);
}
