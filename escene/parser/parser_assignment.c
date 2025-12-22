/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_assignment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 13:42:57 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "../../includes/mini_rt.h"

/**
 * Assigns parsed element lists to primitive scene structure
 * Parses all raw file elements into organized scene components:
 * - Ambient light (only one allowed)
 * - Camera (only one allowed)
 * - Light sources (multiple allowed)
 * - Objects (multiple allowed)
 * @param element_to_conver Raw list of elements from file
 * @param struct_to_assignate Target primitive scene structure to fill
 * @return 0 on success, -1 if any required element is missing
 */
int    primitive_escene_t_asignation(t_list **element_to_conver, t_primitive_escene *struct_to_assignate)
{
    struct_to_assignate->al = general_parser(element_to_conver, ambient_light_parser);
    if(!struct_to_assignate->al)
        return(free(struct_to_assignate), -1);
    struct_to_assignate->camera = general_parser(element_to_conver, camera_parser);
    if(!struct_to_assignate->camera)
        return(free(struct_to_assignate), -1);
    struct_to_assignate->light = general_parser(element_to_conver, light_parser);
    if(!struct_to_assignate->light)
        return(free(struct_to_assignate), -1);
     struct_to_assignate->object = general_parser(element_to_conver, object_parser);
    if(!struct_to_assignate->object)
        return(free(struct_to_assignate), -1);
    return(0);
        
} 

/**
 * Retrieves a specific type of element list from primitive scene
 * @param primitive Primitive scene structure
 * @param identifcator Type of list to retrieve (AL, L, C, OB)
 * @return Pointer to requested list, or NULL if invalid identifier
 */
t_list **get_list_of_elements(t_primitive_escene *primitive, enum  type_list identifcator)
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
