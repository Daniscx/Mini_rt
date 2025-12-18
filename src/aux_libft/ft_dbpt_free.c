/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbpt_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:37:14 by dmaestro          #+#    #+#             */
/*   Updated: 2025/03/22 16:36:17 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		if(dbpt[y])
			free(dbpt[y]);
		y--;
	}
	free(dbpt);
}
