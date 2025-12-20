/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:39:10 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/20 03:08:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*p3;
	unsigned char	*p2;

	if (!s1 || !s2 || n == 0)
		return (0);
	p3 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while ((size_t)i < n && (p3[i] || p2[i]))
	{
		if (p3[i] != p2[i])
			return (p3[i] - p2[i]);
		i++;
	}
	return (0);
}
