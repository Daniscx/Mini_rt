/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_assignment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:57:13 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/parser_internal.h"
# include "../../includes/minirt.h"

static void	free_file_content(t_list **content)
{
	t_list	*aux;
	t_list	*tmp;

	if (!content || !*content)
		return ;
	aux = *content;
	while (aux)
	{
		tmp = aux->next;
		if (aux->content)
			free_double_pointer((char **)aux->content);
		free(aux);
		aux = tmp;
	}
	free(content);
}

int    primitive_escene_t_asignation(t_list **element_to_conver, t_primitive_escene *s)
{
    s->al = general_parser(element_to_conver, ambient_light_parser, free_al_primitive);
    if(!s->al)
        return(free_file_content(element_to_conver), -1);
    s->camera = general_parser(element_to_conver, camera_parser, free_list_camera_primitive);
    if(!s->camera)
    {
        free_al_primitive(s->al);
        return(free_file_content(element_to_conver), -1);
    }
    s->light = general_parser(element_to_conver, light_parser, free_list_of_lights_primitive);
    if(!s->light)
    {
        free_al_primitive(s->al);
        free_list_camera_primitive(s->camera);
        return(free_file_content(element_to_conver), -1);
    }
    s->object = general_parser(element_to_conver, object_parser, list_of_objects_destructor_primitive);
    if(!s->object)
    {
        free_al_primitive(s->al);
        free_list_camera_primitive(s->camera);
        free_list_of_lights_primitive(s->light);
        return(free_file_content(element_to_conver), -1);
    }
    free_file_content(element_to_conver);
    return(0);
}

t_list	**get_list_of_elements(t_primitive_escene *primitive,
	enum e_type_list identifcator)
{
    if(identifcator == AL)
        return(primitive->al);
    else if(identifcator == L)
        return(primitive->light);
    else if(identifcator == C)
        return(primitive->camera);
    else if(identifcator == OB)
        return(primitive->object);
    return(NULL);
}
