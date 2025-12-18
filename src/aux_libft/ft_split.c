/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:46:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/16 14:02:20 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_extractor(char const *n, size_t k, size_t s, char t)
{
	size_t	j;

	j = 0;
	while (s < k)
	{
		if (n[s] == t)
			j++;
		s++;
	}
	return (j - 1);
}

static char	*ft_survivor(char const *n, size_t k, size_t s, char t)
{
	char	*p2;
	char	*p1;
	size_t	i;
	size_t	p;

	i = 0;
	p2 = NULL;
	p1 = (char *)n;
	p = ft_extractor(n, k, s, t);
	p2 = malloc(k - s - p);
	if (!p2)
		return (NULL);
	while (s < k)
	{
		while (p1[s] == t)
			s++;
		p2[i] = p1[s];
		s++;
		i++;
	}
	p2[i] = '\0';
	return (p2);
}

static size_t	ft_worldette(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**ft_rapt(char const *s, char c, char **p3, size_t p)
{
	size_t	r;
	size_t	n;

	r = -1;
	n = 0;
	while (s[p])
	{
		p++;
		if (s[p] == c || s[p] == '\0')
		{
			if (s[p - 1] != c)
			{
				p3[++r] = ft_survivor(s, p, n, c);
				if (!p3[r])
				{
					while (r != 0)
						free(p3[r-- - 1]);
					free(p3);
					return (NULL);
				}
				n = p;
			}
		}
	}
	return (p3);
}

char	**ft_split(char const *s, char c)
{
	char	**p3;
	size_t	p;

	p3 = NULL;
	p = 0;
	if (!s)
		return (NULL);
	p3 = (char **)ft_calloc((ft_worldette(s, c) + 1), sizeof(char *));
	if (!p3)
		return (NULL);
	return (ft_rapt(s, c, p3, p));
}
