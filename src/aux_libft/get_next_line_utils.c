/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:50:32 by dmaestro          #+#    #+#             */
/*   Updated: 2024/12/18 19:21:39 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sstrlen(char *ret)
{
	int	i;

	if (!ret)
		return (0);
	i = 0;
	while (ret[i])
		i++;
	return (i);
}

char	*ft_sstrchr(char *s, int j)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)j)
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*ft_sstrjoin(char *temp, char *s)
{
	int		i;
	int		j;
	char	*res;

	if (!s || !temp)
		return (NULL);
	res = NULL;
	j = 0;
	res = (char *)ft_caalloc(ft_sstrlen(s) + ft_sstrlen(temp), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (temp[j])
	{
		res[j] = temp[j];
		j++;
	}
	while (s && s[i] && j < ft_sstrlen(s) + ft_sstrlen(temp))
	{
		res[j] = s[i];
		j++;
		i++;
	}
	return (free(s), free(temp), res);
}

void	*ft_caalloc(size_t nmemb, size_t size)
{
	char	*p1;
	size_t	s;
	size_t	i;

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
