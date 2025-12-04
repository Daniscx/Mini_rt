/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:48:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/23 18:17:38 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cpi(char *p2, char const *s1, char const *s2)
{
	size_t	i;
	size_t	t;

	t = 0;
	i = 0;
	
	while (s1 && s1[i])
	{
		p2[i] = s1[i];
		i++;
	}
	while (s2 && s2[t])
	{
		p2[i] = s2[t];
		i++;
		t++;
	}
	p2[i] = '\0';
	return (p2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	j;
	size_t	s;
	char	*p1;

	
	j = ft_strlen(s1);
	s = ft_strlen(s2);
	p1 = malloc(j + s + 1);
	if (!p1)
		return (NULL);
	return (ft_cpi(p1, s1, s2));
}
