/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escene.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:31:02 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:31:03 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

escene_t *escene_constructor(char *file)
{
	escene_t *escene;

	(void)file;
	escene = malloc(sizeof(escene_t));
	if (!escene)
		return (NULL);
	escene->object = NULL;
	escene->light = NULL;
	escene->al = NULL;
	escene->camera = NULL;
	return (escene);
}

void escene_destructor(escene_t *escene)
{
	if (!escene)
		return;
	free(escene);
}
