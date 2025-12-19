/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:24:19 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 15:12:24 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
