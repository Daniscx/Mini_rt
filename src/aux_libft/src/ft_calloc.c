/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:47:10 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/20 03:08:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
