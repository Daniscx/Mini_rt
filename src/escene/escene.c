/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escene.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:51:58 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:38:56 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/escene.h"

t_scene *escene_constructor(char *file)
{
    t_scene *result;
    t_primitive_escene *primitive_escene;

    result = ft_calloc(1, sizeof(t_scene ));
    primitive_escene = escene_primiteve_contructor(file);
    if(!primitive_escene)
        return(free(result), NULL);
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
