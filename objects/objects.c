/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:25:50 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 18:41:28 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objects.h"
static  t_object *object_costructor(t_list **components);

t_list  **object_list_Constructor(t_list **components)
{
    t_list *aux;
    t_list **result;
    t_object *obj;

    result = ft_calloc(1, sizeof(t_list *));
    if (!components || !*components)
        return (result);
    aux = *components;
    while (aux)
    {
        obj = object_costructor((t_list **)aux->content);
        if (obj)
            ft_lstadd_back(result, ft_lstnew(obj));
        aux = aux->next;
    }
    return (result);
}
static  enum  objects get_identificator(char *name)
{
 
    if (ft_strncmp(name, "cy", 2) == 0)
        return (Cy);
    else if (ft_strncmp(name, "spt", 3) == 0)
        return (Spt);
    else if (ft_strncmp(name, "plc", 3) == 0)
        return (Plc);
    else if (ft_strncmp(name, "pl", 2) == 0)
        return (Pl);
    else if (ft_strncmp(name, "sp", 2) == 0)
        return (Sp);
    else if (ft_strncmp(name, "co", 2) == 0)
        return (Co);
    else
        return (NONE_MANAGE);
        
}
static void *object_selection_create(enum objects identficator, t_list **object, t_object *structs)
{
    if(identficator == Cy)
        return(cylinder_constructor(object, structs));
    else if(identficator == Sp)
        return(sphere_constructor(object, structs, false));
    else if(identficator == Pl)
        return(plane_constructor(object, structs, false));
    else if(identficator == Co)
        return(cone_constructor(object, structs));
    else if(identficator == Plc)
        return(plane_constructor(object, structs, true));
    else if(identficator == Spt)
        return(sphere_constructor(object, structs, true));
    return (NULL);
}
static  t_object *object_costructor(t_list **components)
{
    t_object *result;
    t_list *aux;

    if (!components || !*components)
        return (NULL);
    result = ft_calloc(1, sizeof(t_object));
    aux = *components;
    if (!aux || !aux->content)
        return (result);
    result->identificator = get_identificator((char *)aux->content);
    aux = aux->next;
    result->figure = object_selection_create(result->identificator, &aux, result);
    return (result);
}
void object_destructor(t_object *object)
{
    if(!object)
        return;
    if(object->figure)
        free(object->figure);

    free(object);
}
void list_of_objects_destructor(t_list **objects)
{
    t_list *aux;
    t_list *temp;
    t_object *obj;

    if (!objects || !*objects)
        return;
    aux = *objects;
    while (aux)
    {
        obj = (t_object *)aux->content;
        object_destructor(obj);
        temp = aux;
        aux = aux->next;
        free(temp);
    }
    free(objects);
}

void  print_object(t_object *object)
{
    if (!object)
    {
        printf("Object is NULL\n");
        return;
    }
    printf("Object Identificator: %d\n", object->identificator);
    if(object->identificator == Sp)
    {
        t_sphere *sphere = (t_sphere *)object->figure;
        if (sphere)
        {
            printf("Sphere Center: (%.2f, %.2f, %.2f)\n", sphere->center.x, sphere->center.y, sphere->center.z);
            printf("Sphere Diameter: %.2f\n", sphere->diameter);
            printf("Sphere Color: (%.2f, %.2f, %.2f)\n", sphere->color.x, sphere->color.y, sphere->color.z);
        }
    }
    else if(object->identificator == Pl)
    {
        t_plane *plane = (t_plane *)object->figure;
        if (plane)
        {
            printf("Plane Point: (%.2f, %.2f, %.2f)\n", plane->point.x, plane->point.y, plane->point.z);
            printf("Plane Normal: (%.2f, %.2f, %.2f)\n", plane->normal.x, plane->normal.y, plane->normal.z);
            printf("Plane Color: (%.2f, %.2f, %.2f)\n", plane->color.x, plane->color.y, plane->color.z);
        }
    }
    else if (object->identificator == Cy)
    {
        t_cylinder *cylinder = (t_cylinder *)object->figure;
        if (cylinder)
        {
            printf("Cylinder Center: (%.2f, %.2f, %.2f)\n", cylinder->center.x, cylinder->center.y, cylinder->center.z);
            printf("Cylinder Axis: (%.2f, %.2f, %.2f)\n", cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
            printf("Cylinder Diameter: %.2f\n", cylinder->diameter);
            printf("Cylinder Height: %.2f\n", cylinder->height);
            printf("Cylinder Color: (%.2f, %.2f, %.2f)\n", cylinder->color.x, cylinder->color.y, cylinder->color.z);
        }
    }
    else if (object->identificator == Co)
    {
        t_cone *cone = (t_cone *)object->figure;
        if (cone)
        {
            printf("Cone Apex: (%.2f, %.2f, %.2f)\n", cone->apex.x, cone->apex.y, cone->apex.z);
            printf("Cone Axis: (%.2f, %.2f, %.2f)\n", cone->axis.x, cone->axis.y, cone->axis.z);
            printf("Cone Angle: %.2f\n", cone->angle);
            printf("Cone Height: %.2f\n", cone->height);
            printf("Cone Color: (%.2f, %.2f, %.2f)\n", cone->color.x, cone->color.y, cone->color.z);
        }
    }
}
void print_list_of_objects(t_list **objects)
{
    t_list *aux;
    t_object *obj;
    int index = 0;

    if (!objects || !*objects)
    {
        printf("No objects to display.\n");
        return;
    }
    aux = *objects;
    printf("List of Objects:\n");
    while (aux)
    {
        obj = (t_object *)aux->content;
        printf("Object %d:\n", index);
        print_object(obj);
        aux = aux->next;
        index++;
    }
}
