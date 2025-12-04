/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:24:19 by dmaestro          #+#    #+#             */
/*   Updated: 2025/03/01 00:52:22 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*t;

	if (!s)
		return (NULL);
	t = NULL;
	while (*s)
	{
		if (*s == (char)c)
			t = (char *)s;
		s++;
	}
	if (*s == (char)c)
		t = ((char *)s);
	return (t);
}
