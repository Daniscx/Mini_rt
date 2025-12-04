/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:26:06 by dmaestro          #+#    #+#             */
/*   Updated: 2024/09/19 13:26:08 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*found;
	size_t	n;
	size_t	i;

	if (*little == '\0')
		return ((char *)big);
	found = (char *)little;
	i = 0;
	while ((i < len) && big[i])
	{
		n = 0;
		while (big[i + n] == found[n] && i + n < len)
		{
			if (found[n] == '\0')
				return ((char *)&big[i]);
			n++;
		}
		if (found[n] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
