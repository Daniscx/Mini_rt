/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 02:25:32 by dmaestro          #+#    #+#             */
/*   Updated: 2025/02/12 19:18:15 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readme(int fd, char *fv)
{
	char	*buffer;
	int		i;

	buffer = NULL;
	buffer = ft_caalloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (free(fv), NULL);
	i = read(fd, buffer, BUFFER_SIZE);
	if (i < 0)
	{
		if (fv)
			free(fv);
		return (free(buffer), NULL);
	}
	if (i == 0)
		return (free(buffer), fv);
	if (fv)
	{
		buffer = ft_sstrjoin(fv, buffer);
		if (!buffer)
			return (free(fv), NULL);
	}
	return (buffer);
}

char	*ft_ssubstr(char *s)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	if (!s)
		return (NULL);
	result = ft_caalloc(ft_strlen(s), sizeof(char));
	if (!result)
		return (NULL);
	while (*s != '\0')
	{
		result[i] = *s;
		i++;
		s++;
	}
	return (result);
}

char	*ft_ssubnstr(char *s)
{
	int		i;
	char	*result;

	if (!s)
		return (NULL);
	i = 0;
	result = NULL;
	result = ft_caalloc(ft_strchr(s, '\n') - s + 1, sizeof(char));
	if (!result)
		return (NULL);
	result[i] = s[i];
	i++;
	while (s[i] && result[i - 1] != '\n')
	{
		result[i] = s[i];
		i++;
	}
	return (result);
}

char	*ft_extarct(char *fv)
{
	char	*ret;
	char	*p;

	ret = NULL;
	p = fv;
	if (!fv)
		return (NULL);
	while (*fv != '\n' && fv)
		fv++;
	fv++;
	ret = ft_ssubstr(fv);
	if (!ret)
		return (free(p), ret);
	return (free(p), ret);
}

char	*get_next_line(int fd)
{
	static char	*fv = NULL;
	char		*ret;

	ret = fv;
	if (fd < 0 || BUFFER_SIZE <= 0 || FOPEN_MAX < fd)
		return (NULL);
	fv = ft_readme(fd, fv);
	if (!fv)
		return (NULL);
	if (fv && ft_sstrchr(fv, '\n'))
	{
		ret = ft_ssubnstr(fv);
		fv = ft_extarct(fv);
		return (ret);
	}
	if (fv && fv == ret)
	{
		ret = ft_ssubstr(fv);
		free(fv);
		fv = NULL;
		return (ret);
	}
	return (get_next_line(fd));
}
