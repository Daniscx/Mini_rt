/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:34:57 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 15:21:48 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
