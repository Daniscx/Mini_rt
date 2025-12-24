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

# include "../../includes/escene.h"
# include "../../includes/minirt.h"
# include "../../includes/parser_internal.h"

t_scene *escene_constructor(char *file, int *msg)
{
    t_scene             *result;
    t_primitive_escene  *primitive_escene;

    *msg = 0;
    result = ft_calloc(1, sizeof(t_scene ));
    primitive_escene = escene_primiteve_constructor(file, msg);
    if(!primitive_escene)
        return(free(result), NULL);
    if (!primitive_escene->al || !*primitive_escene->al)
        return (escene_primitive_destructor(primitive_escene), free(result), error_manager("Scene must have an ambient light (A).", false), *msg = 1, NULL);
    if (!primitive_escene->camera || !*primitive_escene->camera)
        return (escene_primitive_destructor(primitive_escene), free(result), error_manager("Scene must have a camera (C).", false), *msg = 1, NULL);
    if (!primitive_escene->light || !*primitive_escene->light)
        return (escene_primitive_destructor(primitive_escene), free(result), error_manager("Scene must have at least one light (L).", false), *msg = 1, NULL);
    if (!primitive_escene->object || !*primitive_escene->object)
        return (escene_primitive_destructor(primitive_escene), free(result), error_manager("Scene must have at least one object (sp, pl, cy, co).", false), *msg = 1, NULL);
    result->al = ambient_light_constructor(get_list_of_elements(primitive_escene, AL));
    result->camera = camera_constructor(get_list_of_elements(primitive_escene, C));
    result->object = object_list_Constructor(get_list_of_elements(primitive_escene, OB));
    result->light = light_list_constructor(get_list_of_elements(primitive_escene, L));
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
