/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:04:02 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 15:12:24 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char	*p1;
	char	*p2;
	size_t	i;

	i = 0;
	p1 = (char *)src;
	p2 = (char *)dst;
	if (size == 0)
		return (ft_strlen(src));
	while (p1[i] && i < size - 1)
	{
		p2[i] = p1[i];
		i++;
	}
	p2[i] = '\0';
	return (ft_strlen(src));
}
