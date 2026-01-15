/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escene.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:51:58 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:07:07 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/escene.h"
#include "../../includes/minirt.h"
#include "../../includes/parser_internal.h"

static int	check_required_elements(t_primitive_escene *pe, t_scene *result)
{
	if (!pe->al || !*pe->al)
		return (escene_primitive_destructor(pe), free(result),
			error_manager("Scene must have an ambient light (A).", false), 1);
	if (!pe->camera || !*pe->camera)
		return (escene_primitive_destructor(pe), free(result),
			error_manager("Scene must have a camera (C).", false), 1);
	if (!pe->light || !*pe->light)
		return (escene_primitive_destructor(pe), free(result),
			error_manager("Scene must have at least one light (L).", false), 1);
	if (!pe->object || !*pe->object)
		return (escene_primitive_destructor(pe), free(result),
			error_manager("Scene must have at least one object.", false), 1);
	return (0);
}

t_scene	*escene_constructor(char *file, int *msg)
{
	t_scene				*result;
	t_primitive_escene	*primitive_escene;

	*msg = 0;
	result = ft_calloc(1, sizeof(t_scene));
	primitive_escene = escene_primiteve_constructor(file, msg);
	if (!primitive_escene)
		return (free(result), NULL);
	if (check_required_elements(primitive_escene, result))
		return (*msg = 1, NULL);
	result->al = ambient_light_constructor(get_list_of_elements(
				primitive_escene, AL));
	result->camera = camera_constructor(get_list_of_elements(primitive_escene,
				C));
	result->object = object_list_constructor(get_list_of_elements(
				primitive_escene, OB));
	result->light = light_list_constructor(get_list_of_elements(
				primitive_escene, L));
	escene_primitive_destructor(primitive_escene);
	return (result);
}

void	escene_destructor(t_scene *escene)
{
	if (!escene)
		return ;
	if (escene->al)
		ambient_light_destructor(escene->al);
	if (escene->camera)
		camera_destructor(escene->camera);
	if (escene->light)
		light_list_destructor(escene->light);
	if (escene->object)
		list_of_objects_destructor(escene->object);
	free(escene);
}
