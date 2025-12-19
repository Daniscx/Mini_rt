/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:25:20 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 15:12:24 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
