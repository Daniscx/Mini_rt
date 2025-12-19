/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbpt_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:37:14 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 21:18:10 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	free_double_pointer(char **dbpt)
{
	int	y;

	if (!dbpt)
		return ;
	y = 0;
	while (dbpt[y])
		y++;
	y--;
	while (y >= 0)
	{
		if (dbpt[y])
			free(dbpt[y]);
		y--;
	}
	free(dbpt);
}
