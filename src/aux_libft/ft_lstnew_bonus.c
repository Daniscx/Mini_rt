/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:34:57 by dmaestro          #+#    #+#             */
/*   Updated: 2024/10/10 14:47:55 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnod;

	newnod = (t_list *)malloc(sizeof(t_list));
	if (!newnod)
		return (NULL);
	newnod->content = content;
	newnod->next = NULL;
	return (newnod);
}
