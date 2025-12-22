/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 14:41:10 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "stdbool.h"
#include "../../includes/mini_rt.h"

/**
 * Parses ambient light element from .rt file
 * Format: A <ratio> <color_rgb>
 * ratio: 0 to 1 (brightness ratio)
 * color_rgb: r,g,b (each 0-255)
 * @param actual_element Array with ["A", ratio, color]
 * @param list_to_add_element List to append parsed data to
 */
int ambient_light_parser(char **actual_element, t_list **list_to_add_element)
{
    int i;
    char **rgb_to_split;
    float *actual_float;
    
    i = 1;
    if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) == 0 && *list_to_add_element) 
       return (ft_printf("%s\n","multiple ambient light declaration detected please check"), -1);
    else if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) != 0 )
        return (0); 
    while(actual_element[1][i])
    {
        if(ft_isdigit(actual_element[1][i]) == 0 && actual_element[1][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in ambient light ratio");
            free(list_to_add_element);
            return (-1);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float)); 
    *actual_float = ft_float(actual_element[1]);
     if(if_betwen_values(*actual_float, 0,  1) == false)
            return(ft_printf("%s\n","no valid parametter find in ambient light ratio") ,-1);
    ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
    rgb_to_split = ft_split(actual_element[2], ',');
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_of_float_checker(rgb_to_split, 255 , 0, true)));
    return(0);
}

/**
 * Parses light element from .rt file
 * Format: L <position_xyz> <brightness> [<color_rgb>]
 * position_xyz: x,y,z coordinates
 * brightness: 0 to 1
 * color_rgb: optional, default is 255,255,255 (white), values 0-255
 * @param actual_element Array with ["L", position, brightness, [color]]
 * @param list_to_add_element List to append parsed light data to
 */
int light_parser(char **actual_element, t_list **list_to_add_element)
{
    t_list **new_light_element;
    char **splited_element;
    int i;
    float *actual_float;
    
    i = 0;
    
    if(ft_strncmp(actual_element[0], "L", ft_strlen(actual_element[1])))
        return (0);
    new_light_element = ft_calloc(1,sizeof(t_list *));
    splited_element = ft_split(actual_element[1], ',');
    if(!splited_element || *splited_element == NULL)
        return (-1);
    ft_lstadd_front(new_light_element, ft_lstnew(list_of_float_checker(splited_element, 0, 0, false)));
    while(actual_element[2][i])
    {
        if(ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in light ratio");
            free(list_to_add_element);
            return (-1);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_float(actual_element[2]);
    ft_lstadd_back(new_light_element, ft_lstnew(actual_float));
    if(!actual_element[3])
        actual_element[3] = ft_strdup("255,255,255"); 
    splited_element = ft_split(actual_element[3], ',');
    if(!splited_element || *splited_element == NULL)
        return(free(list_to_add_element), -1);
    ft_lstadd_back(new_light_element, ft_lstnew(list_of_float_checker(splited_element, 255 , 0, true)));
    ft_lstadd_back(list_to_add_element, ft_lstnew(new_light_element));
    return(0);    
}

/**
 * Parses camera element from .rt file
 * Format: C <position_xyz> <normal_vector_xyz> <fov>
 * position_xyz: x,y,z coordinates
 * normal_vector_xyz: normalized direction vector (each component -1 to 1)
 * fov: field of view angle (0 to 180)
 * @param actual_element Array with ["C", position, vector, fov]
 * @param list_to_add_element List to append parsed camera data to
 */
int camera_parser(char **actual_element, t_list **list_to_add_element)
{ 
    int i;
    char **x_y_z_to_split;
    float *actual_float;
    t_list **list_float;
    
    
    i = 0;
    if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) == 0 && *list_to_add_element) 
        return(ft_printf("%s\n","multiple Camaera declaration detected please check"), -1);
    else if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) != 0 )
        return (0);
    x_y_z_to_split = ft_split(actual_element[1], ',');
    list_float = list_of_float_checker(x_y_z_to_split, 0 , 0, false);
    if(!list_float)
    {
        ft_printf("%s\n", "camera_element");
        return(free(list_to_add_element), -1);
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    x_y_z_to_split = ft_split(actual_element[2], ',');
    list_float = list_of_float_checker(x_y_z_to_split, 0 , 0, false);
    if(!list_float)
    {
        ft_printf("%s\n", "camera_element");
        return(free(list_to_add_element), -1);
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    i = 0;
    if(actual_element[3][i] == '-')
        i++;
    while(actual_element[3][i])
    {
        if(ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in ambient light ratio");
            free(list_to_add_element);
            return(-1); 
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float *));
    *actual_float = ft_float(actual_element[3]);
    if(if_betwen_values(*actual_float, 0, 180) == false)
        return(ft_printf("%s\n","no valid parametter find in camera vector"), free(list_to_add_element), -1);
    ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
    return (0);
}

/**
 * Parses sphere object from .rt file
 * Format: sp <center_xyz> <diameter> <color_rgb>
 * center_xyz: x,y,z coordinates
 * diameter: positive number
 * color_rgb: r,g,b (each 0-255)
 * @param actual_element Array with ["sp", center, diameter, color]
 * @return Pointer to list with parsed sphere data, NULL on error
 */
static t_list **sphere_parser(char **actual_element)
{
    t_list **result;
    t_list **float_list;
    char **element_splited;
    int i;
    float   *actual_float;

    
    
    result = ft_calloc(1, sizeof(t_list *));
    ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
    element_splited = ft_split(actual_element[1], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false);
    free_double_pointer(element_splited);
     if(!float_list)
    {
        ft_printf("%s\n", "sphere element");
        return(free(result),NULL);
    }
     ft_lstadd_back(result, ft_lstnew(float_list));
     i = 0;
     if(actual_element[2][i] == '-')
            i++;
     while(actual_element[2][i])
    {
        if(ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in sphere diametre");
            free(result);
            return (NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_float(actual_element[2]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    element_splited = ft_split(actual_element[3], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true);
    free_double_pointer(element_splited);
    if(!float_list)
    {
        ft_printf("%s\n", "sphere element");
        return(free(result),NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    if(actual_element[4])
    {
        i = open(actual_element[4], O_RDONLY);
        if(i < 0)
            return(ft_printf("%s\n","the texture file dont exist please check the path"), free(result),NULL);
        close(i);
        ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[4])));
        if(actual_element[5])
        {
            i = open(actual_element[5], O_RDONLY);
            if(i < 0)
                return(ft_printf("%s\n","the texture file dont exist please check the path"), free(result),NULL);
            close(i);
            ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[5])));
        }
    }
    return(result);
}

/**
 * Parses plane object from .rt file
 * Format: pl <point_xyz> <normal_vector_xyz> <color_rgb>
 * point_xyz: x,y,z coordinates of a point on the plane
 * normal_vector_xyz: perpendicular vector to the plane (normalized, -1 to 1)
 * color_rgb: r,g,b (each 0-255)
 * @param actual_element Array with ["pl", point, vector, color]
 * @return Pointer to list with parsed plane data, NULL on error
 */
static t_list **plane_parser(char **actual_element)
{
    t_list **result;
    t_list **float_list;
    char **element_splited;
        
    result = ft_calloc(1, sizeof(t_list *));
    ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
    element_splited = ft_split(actual_element[1], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false);
    free_double_pointer(element_splited);
     if(!float_list)
    {
        ft_printf("%s\n", "plane position");
        return(free(result),NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[2], ',');
    float_list = list_of_float_checker(element_splited, 1, -1, true);
    free_double_pointer(element_splited);
      if(!float_list)
    {
        ft_printf("%s\n", "plane vector");
        return(free(result),NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[3], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true);
    free_double_pointer(element_splited);
      if(!float_list)
    {
        ft_printf("%s\n", "plane color");
        return(free(result),NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    return(result);
}

/**
 * Parses cylinder object from .rt file
 * Format: cy <center_xyz> <normal_vector_xyz> <diameter> <height> <color_rgb>
 * center_xyz: x,y,z coordinates
 * normal_vector_xyz: axis direction (normalized, -1 to 1)
 * diameter: positive number
 * height: positive number
 * color_rgb: r,g,b (each 0-255)
 * @param actual_element Array with ["cy", center, vector, diameter, height, color]
 * @return Pointer to list with parsed cylinder data, NULL on error
 */
static t_list **cylindrer_parser(char **actual_element)
{
    t_list **result;
    t_list **float_list;
    char **element_splited;
    int i;
    float   *actual_float;
    
    result = ft_calloc(1, sizeof(t_list *));
    ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
    element_splited = ft_split(actual_element[1], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false);
    free_double_pointer(element_splited);
    if(!float_list)
        return(ft_printf("%s\n","cylindrer position"), free(result),NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[2], ',');
    float_list = list_of_float_checker(element_splited, 1, -1, true);
    free_double_pointer(element_splited);
    if(!float_list)
        return(ft_printf("%s\n","cylindrer vector"), free(result),NULL);     
    ft_lstadd_back(result, ft_lstnew(float_list));
    i = 0;
    if(actual_element[3][i] == '-')
        i++;
    while(actual_element[3][i])
    {
        if(ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in cylindrer diametre");
            free(result);
            return (NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_float(actual_element[3]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    i = 0;
    if(actual_element[4][i] == '-')
        i++;
     while(actual_element[4][i])
    {
        if(ft_isdigit(actual_element[4][i]) == 0 && actual_element[4][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in cylindrer hight");
            free(result);
            return (NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_float(actual_element[4]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    element_splited = ft_split(actual_element[5], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true);
    free_double_pointer(element_splited);
    if(!float_list)
       return(ft_printf("%s\n","cylindrer rgb"), free(result),NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    return(result);
}

/**
 * Generic parser dispatcher for all objects
 * Determines object type and calls appropriate parser
 * Supports: sp (sphere), spt (sphere textured), pl (plane), plc (plane colored), 
 *           cy (cylinder), co (cone)
 * @param actual_element Array with object type and parameters
 * @param list_to_add_element List to append parsed object to
 */
int object_parser(char **actual_element, t_list **list_to_add_element)
{
    size_t len;
    t_list **result;
    
    len = ft_strlen(actual_element[0]);
    if(ft_strncmp(actual_element[0], "sp", len) == 0 || ft_strncmp(actual_element[0], "spt", len) == 0)
    {
        result = sphere_parser(actual_element);
        if(!result)
            return(free(list_to_add_element), -1);
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
        if(ft_strncmp(actual_element[0], "pl", len) == 0 || ft_strncmp(actual_element[0], "plc", len) == 0 )
    {
        result = plane_parser(actual_element);
        if(!result)
            return(free(list_to_add_element), -1);
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
        if(ft_strncmp(actual_element[0], "cy", len) == 0 || ft_strncmp(actual_element[0], "co", len) == 0)
    {
        result = cylindrer_parser(actual_element);
        if(!result)
            return(free(list_to_add_element), -1);
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
    return(0);
}

/**
 * Generic parser for all scene elements
 * Uses function pointers to dispatch to specific parsers
 * @param list__to_track List of unparsed elements from file
 * @param f Function pointer to appropriate element parser
 * @return Pointer to parsed element list, NULL on error
 */
t_list **general_parser(t_list    **list__to_track, int f(char **,t_list **))
{
    t_list **result;
    t_list *actual_node;

    if(!list__to_track || *list__to_track == NULL)
        return(NULL);
    result = ft_calloc(1, sizeof(t_list *));
    actual_node = *list__to_track;
    while(actual_node)
    {
        if(correct_number_of_elements(actual_node->content) == false)
            return(free(result), NULL);
        if(f(actual_node->content, result) == -1)
            return(free(result), NULL);
        actual_node = actual_node->next;
    }
    if(result && *result == NULL)
        return(free(result), NULL);
    return(result);
    
}
