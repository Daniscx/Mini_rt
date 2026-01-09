/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destructors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2026/01/09 15:18:56 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "../../includes/mini_rt.h"

/**
 * Frees a linked list of floats
 * Frees each node's content (float*) and the node itself
 * @param list Pointer to list head pointer to free
 */
void free_list_of_floats(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;

    if(!list || *list == NULL)
        return;
    actual_node = *list;
    while(actual_node)
    {
        aux_node = actual_node->next;
        if(actual_node->content)
                free(actual_node->content);
        free(actual_node);
        actual_node = aux_node;
    }
    if (list)
        free(list);
}

/**
 * Frees an ambient light primitive structure
 * Ambient light has: [identifier, ratio_float, rgb_list**]
 * @param list Linked list representing ambient light data
 */
void free_al_primitive(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;
  

    if(!list || *list == NULL)
        return;
    actual_node = *list;
    if(actual_node->content)
        free(actual_node->content);
    aux_node = actual_node->next;
    if(aux_node)
    {
        actual_list = (t_list **)aux_node->content;
        free_list_of_floats(actual_list);
        free(aux_node);
    }
    free(actual_node);
    free(list);
}

/**
 * Frees a single light primitive structure from a list
 * Light has: [position_list**, brightness_float, color_list**]
 * @param list Linked list representing light data
 */
void free_primitive_light(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;

    if(!list || *list == NULL)
        return;
    aux_node = *list;
    if(aux_node->content)
        free(aux_node->content);
    actual_node = aux_node->next;
    free(aux_node);
    if(actual_node)
        free(actual_node->content);
    aux_node = actual_node->next;
    free(actual_node);
    if(aux_node)
    {
        actual_list = (t_list **)aux_node->content;
        free_list_of_floats(actual_list);
        free(aux_node);
    }
    free(list);
}

/**
 * Frees the entire list of light primitives
 * Each node contains a t_list** representing one light
 * @param list Linked list of lights
 */
void free_list_of_lights_primitive(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;

    if(!list || *list == NULL)
        return;
    actual_node = *list;
    while(actual_node)
    {
        aux_node = actual_node->next;
        actual_list = (t_list **)actual_node->content;
        free_primitive_light(actual_list);
        free(actual_node);
        actual_node = aux_node;
    }
    free(list);
}

/**
 * Frees a camera primitive structure
 * Camera has: [position_list**, direction_list**, fov_float]
 * @param list Linked list representing camera data
 */
void free_list_camera_primitive(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;
    
    if(!list || *list == NULL)
        return;
    actual_node = *list;
    if(actual_node->content)
        free_list_of_floats(actual_node->content);
    aux_node = actual_node->next;
    free(actual_node);
    if(aux_node)
    {
        actual_list = (t_list **)aux_node->content;
        free_list_of_floats(actual_list);
        actual_node = aux_node->next;
    }
    if(actual_node)
    {
        if(actual_node->content)
            free(actual_node->content);
        free(actual_node);
    } 
    free(list);
}

/**
 * Frees a sphere primitive structure
 * Sphere has: [identifier, center_list**, diameter_float, color_list**]
 * @param list Linked list representing sphere data
 */
void primitive_sphere_destructor(t_list **list)
{   
     t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;

    if(!list || *list == NULL)
        return;
    actual_node = *list;
    if(actual_node->content)
        free(actual_node->content);
    aux_node = actual_node->next;
    if(aux_node)
    {
        actual_list = (t_list **)aux_node->content;
        free_list_of_floats(actual_list);
        free(aux_node);
    }
    if(actual_node)
    { 
        free(actual_node->content);
        aux_node = actual_node->next;
        free(actual_node);
    }
    if(aux_node)
    {
        actual_list = (t_list **)aux_node->content;
        free_list_of_floats(actual_list);
        actual_node = aux_node->next;
        free(aux_node);
    }
    if(actual_node)
    {
        if(actual_node->content)
            free(actual_node->content);
        aux_node = actual_node->next;
        free(actual_node);
    }
    if(aux_node)
    {
        if(aux_node->content)
            free(aux_node->content);
        free(aux_node);
    }
    free(list);
    
}

void general_destructor(t_list **components, char *position)
{
    int i;
    t_list *aux;
    t_list *node;
    
    aux = *components;
    i = 0;
    while(aux)
    {

        if(ft_strchr(position, ft_itoa(i)[0]))
            free_list_of_floats(aux->content);
        else
            free(aux->content);
        node = aux ;
        aux = aux->next;
        free(node);
        i++;
    }
    free(components);
}
/**
 * Frees a plane primitive structure
 * Plane has: [identifier, position_list**, normal_list**, color_list**]
 * @param list Linked list representing plane data
 */
void primitive_plane_destructor(t_list **list)
{   
     t_list *actual_node;
    t_list *aux_node;

    if(!list || *list == NULL)
        return;
    actual_node = *list;
    if(actual_node->content)
        free(actual_node->content);
    aux_node = actual_node->next;
    if(aux_node)
    {
        free_list_of_floats(aux_node->content);
        actual_node = aux_node->next;
        free(aux_node);
    }
    if(actual_node)
    { 
        free_list_of_floats(actual_node->content);
        aux_node = actual_node->next;
        free(actual_node);
    }
    if(aux_node)
    {
        free_list_of_floats(aux_node->content);
        free(aux_node);
    }
    free(list);
    
}

/**
 * Frees a cylinder primitive structure
 * Cylinder has: [identifier, center_list**, axis_list**, diameter_float, height_float, color_list**]
 * @param list Linked list representing cylinder data
 */
void primitive_cylinder_destructor(t_list **list)
{   
     t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;

    if(!list || *list == NULL)
        return;
    actual_node = *list;
    if(actual_node->content)
        free(actual_node->content);
    aux_node = actual_node->next;
    if(aux_node)
    {
        actual_list = (t_list **)aux_node->content;
        free_list_of_floats(actual_list);
        free(aux_node);
    }
    if(actual_node)
    { 
        free_list_of_floats(actual_node->content);
        aux_node = actual_node->next;
        free(actual_node);
    }
    if(aux_node)
    {
        if(aux_node->content)
            free(aux_node->content);
        actual_node = aux_node->next;
        free(aux_node);
    }
    if(actual_node)
    {
        if(actual_node->content)
            free(actual_node->content);
        aux_node = actual_node->next;
        free(actual_node);
    }
    if(aux_node)
    {
        actual_list = (t_list **)aux_node->content;
        free_list_of_floats(actual_list);
        free(aux_node);
    }
    free(list);
    
}

/**
 * Dispatcher function to free object primitives based on type
 * Handles: sp (sphere), pl (plane), cy (cylinder), co (cone)
 * @param list Linked list representing object data
 * @param identificator Object type string
 */
void primitive_destructor_selector(t_list **list, char *identificator)
{
    size_t len;

    printf("destruyendo : %s\n", "teta");
    len = ft_strlen(identificator);
   if(ft_strncmp(identificator, "sp", len) == 0 || ft_strncmp(identificator, "spt", len) == 0)
      general_destructor(list,"13" );
   else if(ft_strncmp(identificator, "pl", len) == 0 || ft_strncmp(identificator, "plc", len) == 0)
        general_destructor(list, "123");
   else if(ft_strncmp(identificator, "cy", len) == 0 || ft_strncmp(identificator, "co", len) == 0)
        primitive_cylinder_destructor(list);
}

/**
 * Frees the entire list of object primitives
 * Each node contains a t_list** representing one object
 * Calls type-specific destructors based on object identifier
 * @param list Linked list of objects
 */
void list_of_objects_destructor_primitive(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;
    t_list *content_node;

    if(!list || *list == NULL)
        return;
    actual_node = *list;
    while(actual_node)
    {
        aux_node = actual_node->next;
        actual_list = (t_list **)actual_node->content;
        content_node = *actual_list;
        primitive_destructor_selector(actual_list   , (char *)content_node->content);
        free(actual_node);
        actual_node = aux_node;
    }
    free(list);
}

/**
 * Frees the entire primitive scene structure
 * Frees all sub-lists: ambient light, camera, lights, objects
 * @param primitive Primitive scene structure to free
 */
void escene_primitive_destructor(t_primitive_escene *primitive)
{
    if(!primitive)
        return;
    if(primitive->al)
        free_al_primitive(primitive->al);
    if(primitive->camera)
        free_list_camera_primitive(primitive->camera);
    if(primitive->light)
        free_list_of_lights_primitive(primitive->light);
    if(primitive->object)
       list_of_objects_destructor_primitive(primitive->object);
    free(primitive);
}
void list_of_db_array_destructor(t_list **element)
{
    t_list *aux;
    t_list *next;

    aux = *element;

    while(aux)
    {
        next = aux->next;
        free_double_pointer(aux->content);
        free(aux);
        aux  = next;
    }
    free(element);
}
