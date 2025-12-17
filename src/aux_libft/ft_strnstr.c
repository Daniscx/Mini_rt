/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:26:06 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/16 19:26:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
