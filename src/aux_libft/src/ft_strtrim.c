/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:57:08 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/20 03:08:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	j;

	s = 0;
	j = ft_strlen(s1);
	if (!s1 && !set)
		return ((char *)malloc(1));
	while (ft_strchr(set, s1[s]) && s1[s] != '\0')
		s++;
	while (ft_strchr(set, s1[j]) && j > 0)
		j--;
	return (ft_substr(s1, s, (j - s + 1)));
}
