/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/14 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"

t_list	**get_list_of_elements(t_primitive_escene *primitive,
		enum e_type_list identifcator)
{
	if (identifcator == AL)
		return (primitive->al);
	else if (identifcator == L)
		return (primitive->light);
	else if (identifcator == C)
		return (primitive->camera);
	else if (identifcator == OB)
		return (primitive->object);
	return (NULL);
}
