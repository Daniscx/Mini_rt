/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destructors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:22:17 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/parser_internal.h"
# include "../../includes/minirt.h"

void free_list_of_floats(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;

    if (!list)
        return ;
    if (*list == NULL)
        return (free(list));
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

void free_al_primitive(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;

    if (!list)
        return ;
    if (*list == NULL)
        return (free(list));
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

void free_primitive_light(t_list **list)
{
    t_list	*node;
    t_list	*next;
    int		idx;

    if (!list)
        return ;
    if (*list == NULL)
        return (free(list));
    node = *list;
    idx = 0;
    while (node)
    {
        next = node->next;
        if (node->content)
        {
            if (idx == 0 || idx == 2)
                free_list_of_floats((t_list **)node->content);
            else
                free(node->content);
        }
        free(node);
        node = next;
        idx++;
    }
    free(list);
}

void free_list_of_lights_primitive(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;

    if (!list)
        return ;
    if (*list == NULL)
        return (free(list));
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

void free_list_camera_primitive(t_list **list)
{
    t_list	*node;
    t_list	*next;
    int		idx;

    if (!list)
        return ;
    if (*list == NULL)
        return (free(list));
    node = *list;
    idx = 0;
    while (node)
    {
        next = node->next;
        if (node->content)
        {
            if (idx == 0 || idx == 1)
                free_list_of_floats((t_list **)node->content);
            else
                free(node->content);
        }
        free(node);
        node = next;
        idx++;
    }
    free(list);
}

void primitive_sphere_destructor(t_list **list)
{   
    t_list *node;
    t_list *next;
    int idx;

    if(!list || *list == NULL)
        return;
    node = *list;
    idx = 0;
    while (node)
    {
        next = node->next;
        if (node->content)
        {
            if (idx == 1 || idx == 3)
                free_list_of_floats((t_list **)node->content);
            else
                free(node->content);
        }
        free(node);
        node = next;
        idx++;
    }
    free(list);
}

void primitive_plane_destructor(t_list **list)
{   
    t_list *node;
    t_list *next;
    int idx;

    if(!list || *list == NULL)
        return;
    node = *list;
    idx = 0;
    while (node)
    {
        next = node->next;
        if (node->content)
        {
            if (idx == 1 || idx == 2 || idx == 3)
                free_list_of_floats((t_list **)node->content);
            else
                free(node->content);
        }
        free(node);
        node = next;
        idx++;
    }
    free(list);
}

void primitive_cylinder_destructor(t_list **list)
{   
    t_list *node;
    t_list *next;
    int idx;

    if(!list || *list == NULL)
        return;
    node = *list;
    idx = 0;
    while (node)
    {
        next = node->next;
        if (node->content)
        {
            if (idx == 1 || idx == 2 || idx == 5)
                free_list_of_floats((t_list **)node->content);
            else
                free(node->content);
        }
        free(node);
        node = next;
        idx++;
    }
    free(list);
}

void primitive_destructor_selector(t_list **list, char *identificator)
{
    size_t len;

    len = ft_strlen(identificator);
    if(ft_strncmp(identificator, "cy", len) == 0 || ft_strncmp(identificator, "co", len) == 0)
        primitive_cylinder_destructor(list);
    else if(ft_strncmp(identificator, "sp", 2) == 0 || ft_strncmp(identificator, "spt", 3) == 0)
        primitive_sphere_destructor(list);
    else if(ft_strncmp(identificator, "pl", 2) == 0 || ft_strncmp(identificator, "plc", 3) == 0)
        primitive_plane_destructor(list);
}

void list_of_objects_destructor_primitive(t_list **list)
{
    t_list *actual_node;
    t_list *aux_node;
    t_list **actual_list;
    t_list *content_node;

    if (!list)
        return ;
    if (*list == NULL)
        return (free(list));
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
