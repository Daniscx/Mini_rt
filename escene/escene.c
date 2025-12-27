/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escene.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:51:58 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/27 18:49:36 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/escene.h"

t_scene *escene_constructor(char *file)
{
    t_scene *result;
    t_primitive_escene *primitive_escene;

    result = ft_calloc(1, sizeof(t_scene ));

    primitive_escene = escene_primiteve_contructor(file);
    if(!primitive_escene)
        return(NULL);
    result->al = ambient_light_constructor(get_list_of_elements(primitive_escene, AL));
    result->camera =camera_constructor(get_list_of_elements(primitive_escene, C));
    result->object = object_list_Constructor(get_list_of_elements(primitive_escene, OB));
    result->light = light_list_constructor(get_list_of_elements(primitive_escene, L));
   // print_escene(result);
    escene_primitive_destructor(primitive_escene);
    return(result);
    
}
/*void escene_destructor(t_escene *escene)
{
    if(!escene)
        return;
    if(escene->al)
        ambient_light_destructor(escene->al);
    if(escene->camera)
        camera_destructor(escene->camera);
    if(escene->light)
        light_list_destructor(escene->light);
    if(escene->object)
        object_list_destructor(escene->object);
    free(escene);
}*/
/*void print_escene(t_escene *scene)
{
    if (!scene)
    {
        printf("Scene is NULL\n");
        return;
    }
    printf("=== Scene Information ===\n");
    if (scene->al)
        print_ambient_light(scene->al);
    else
        printf("No Ambient Light\n");
    
    if (scene->camera)
        print_camera(scene->camera);
    else
        printf("No Camera\n");
    
    if (scene->light)
        print_list_of_lights(scene->light);
    else
        printf("No Lights\n");
    
    if (scene->object)
        print_list_of_objects(scene->object);
    else
        printf("No Objects\n");
    
    printf("=========================\n");
}*/