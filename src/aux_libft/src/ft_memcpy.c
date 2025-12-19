/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 15:13:07 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
