/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:35:50 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/20 03:08:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*p3;

	if (!s || !f)
		return (NULL);
	p3 = (char *)malloc(ft_strlen(s) + 1);
	if (!p3)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		p3[i] = f(i, s[i]);
		i++;
	}
	p3[i] = '\0';
	return (p3);
}
