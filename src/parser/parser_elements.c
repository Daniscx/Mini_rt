/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 04:02:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/parser_internal.h"
# include "../../includes/minirt.h"

int ambient_light_parser(char **actual_element, t_list **list_to_add_element)
{
    int     i;
    char    **rgb_to_split;
    float   *actual_float;
    t_list  **list_float;

    i = 1;
    if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) == 0 && *list_to_add_element)
        return (error_manager("Multiple ambient light declarations detected.", false), -1);
    else if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) != 0)
        return (0);
    while(actual_element[1][i])
    {
        if(ft_isdigit(actual_element[1][i]) == 0 && actual_element[1][i] != '.')
        {
            error_manager("No valid parameter found in ambient light ratio.", false);
            return (-1);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[1]);
    if(if_betwen_values(*actual_float, 0,  1) == false)
    {
        free(actual_float);
        return(error_manager("No valid parameter found in ambient light ratio.", false), -1);
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
    rgb_to_split = ft_split(actual_element[2], ',');
    list_float = list_of_float_checker(rgb_to_split, 255 , 0, true);
    free_double_pointer(rgb_to_split);
    if(!list_float)
        return(ft_putstr_fd("ambient light color.\n", 2), -1);
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    return(0);
}

int light_parser(char **actual_element, t_list **list_to_add_element)
{
    t_list **new_light_element;
    t_list **list_float;
    char **splited_element;
    int i;
    float *actual_float;

    i = 0;
    if(ft_strncmp(actual_element[0], "L", ft_strlen(actual_element[1])))
        return (0);
    new_light_element = ft_calloc(1, sizeof(t_list *));
    splited_element = ft_split(actual_element[1], ',');
    if(!splited_element || *splited_element == NULL)
        return (free(new_light_element), -1);
    list_float = list_of_float_checker(splited_element, 0, 0, false);
    free_double_pointer(splited_element);
    if(!list_float)
    {
        ft_putstr_fd("light position.\n", 2);
        return(free(new_light_element), -1);
    }
    ft_lstadd_front(new_light_element, ft_lstnew(list_float));
    while(actual_element[2][i])
    {
        if(ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
        {
            error_manager("No valid parameter found in light brightness.", false);
            free_primitive_light(new_light_element);
            return (-1);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[2]);
    if(if_betwen_values(*actual_float, 0, 1) == false)
    {
        free(actual_float);
        free_primitive_light(new_light_element);
        return(error_manager("No valid parameter found in light brightness.", false), -1);
    }
    ft_lstadd_back(new_light_element, ft_lstnew(actual_float));
    if(!actual_element[3])
        actual_element[3] = ft_strdup("255,255,255");
    splited_element = ft_split(actual_element[3], ',');
    if(!splited_element || *splited_element == NULL)
    {
        free_primitive_light(new_light_element);
        return(-1);
    }
    list_float = list_of_float_checker(splited_element, 255 , 0, true);
    free_double_pointer(splited_element);
    if(!list_float)
    {
        ft_putstr_fd("light color.\n", 2);
        free_primitive_light(new_light_element);
        return(-1);
    }
    ft_lstadd_back(new_light_element, ft_lstnew(list_float));
    ft_lstadd_back(list_to_add_element, ft_lstnew(new_light_element));
    return(0);
}

int camera_parser(char **actual_element, t_list **list_to_add_element)
{
    int i;
    char **x_y_z_to_split;
    float *actual_float;
    t_list **list_float;

    i = 0;
    if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) == 0 && *list_to_add_element)
        return(error_manager("Multiple camera declarations detected.", false), -1);
    else if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) != 0)
        return (0);
    x_y_z_to_split = ft_split(actual_element[1], ',');
    list_float = list_of_float_checker(x_y_z_to_split, 0 , 0, false);
    free_double_pointer(x_y_z_to_split);
    if(!list_float)
    {
        ft_putstr_fd("camera position.\n", 2);
        return(-1);
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    x_y_z_to_split = ft_split(actual_element[2], ',');
    list_float = list_of_float_checker(x_y_z_to_split, 0 , 0, false);
    free_double_pointer(x_y_z_to_split);
    if(!list_float)
    {
        ft_putstr_fd("camera orientation.\n", 2);
        return(-1);
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    i = 0;
    if(actual_element[3][i] == '-')
        i++;
    while(actual_element[3][i])
    {
        if(ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
        {
            error_manager("No valid parameter found in camera FOV.", false);
            return(-1);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[3]);
    if(if_betwen_values(*actual_float, 0, 180) == false)
    {
        free(actual_float);
        return(error_manager("No valid parameter found in camera FOV.", false), -1);
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
    return (0);
}

static t_list **sphere_parser(char **actual_element)
{
    t_list **result;
    t_list **float_list;
    char **element_splited;
    int i;
    float   *actual_float;
    char *texture;

    result = ft_calloc(1, sizeof(t_list *));
    ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
    element_splited = ft_split(actual_element[1], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false);
    free_double_pointer(element_splited);
    if(!float_list)
    {
        ft_putstr_fd("sphere position.\n", 2);
        return(primitive_sphere_destructor(result), NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    i = 0;
    if(actual_element[2][i] == '-')
        i++;
    while(actual_element[2][i])
    {
        if(ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
        {
            error_manager("No valid parameter found in sphere diameter.", false);
            return(primitive_sphere_destructor(result), NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[2]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    element_splited = ft_split(actual_element[3], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true);
    free_double_pointer(element_splited);
    if(!float_list)
    {
        ft_putstr_fd("sphere color.\n", 2);
        return(primitive_sphere_destructor(result), NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    if(actual_element[4])
    {
        texture = parser_texture_name(actual_element[4]);
        if(texture == NULL)
        {
            error_manager("Texture file does not exist.", false);
            return(primitive_sphere_destructor(result), NULL);
        }
        ft_lstadd_back(result, ft_lstnew(texture));
        if(actual_element[5])
        {
            texture = parser_texture_name(actual_element[5]);
            if(texture == NULL)
            {
                error_manager("Texture file does not exist.", false);
                return(primitive_sphere_destructor(result), NULL);
            }
            ft_lstadd_back(result, ft_lstnew(texture));
        }
    }
    return(result);
}

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
        ft_putstr_fd("plane position.\n", 2);
        return(primitive_plane_destructor(result), NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[2], ',');
    float_list = list_of_float_checker(element_splited, 1, -1, true);
    free_double_pointer(element_splited);
    if(!float_list)
    {
        ft_putstr_fd("plane normal vector.\n", 2);
        return(primitive_plane_destructor(result), NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[3], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true);
    free_double_pointer(element_splited);
    if(!float_list)
    {
        ft_putstr_fd("plane color.\n", 2);
        return(primitive_plane_destructor(result), NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    return(result);
}

static t_list **cylinder_parser(char **actual_element)
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
        ft_putstr_fd("cylinder position.\n", 2);
        return(primitive_cylinder_destructor(result), NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[2], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false);
    free_double_pointer(element_splited);
    if(!float_list)
    {
        ft_putstr_fd("cylinder axis vector.\n", 2);
        return(primitive_cylinder_destructor(result), NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    i = 0;
    if(actual_element[3][i] == '-')
        i++;
    while(actual_element[3][i])
    {
        if(ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
        {
            error_manager("No valid parameter found in cylinder diameter.", false);
            return(primitive_cylinder_destructor(result), NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[3]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    i = 0;
    if(actual_element[4][i] == '-')
        i++;
    while(actual_element[4][i])
    {
        if(ft_isdigit(actual_element[4][i]) == 0 && actual_element[4][i] != '.')
        {
            error_manager("No valid parameter found in cylinder height.", false);
            return(primitive_cylinder_destructor(result), NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[4]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    element_splited = ft_split(actual_element[5], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true);
    free_double_pointer(element_splited);
    if(!float_list)
    {
        ft_putstr_fd("cylinder color.\n", 2);
        return(primitive_cylinder_destructor(result), NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    return(result);
}

int object_parser(char **actual_element, t_list **list_to_add_element)
{
    size_t len;
    t_list **result;
    
    len = ft_strlen(actual_element[0]);
    if(ft_strncmp(actual_element[0], "sp", len) == 0 || ft_strncmp(actual_element[0], "spt", len) == 0)
    {
        result = sphere_parser(actual_element);
        if(!result)
            return(-1);
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
        if(ft_strncmp(actual_element[0], "pl", len) == 0 || ft_strncmp(actual_element[0], "plc", len) == 0 )
    {
        result = plane_parser(actual_element);
        if(!result)
            return(-1);
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
    if(ft_strncmp(actual_element[0], "cy", len) == 0 || ft_strncmp(actual_element[0], "co", len) == 0)
    {
        result = cylinder_parser(actual_element);
        if(!result)
            return(-1);
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
    return(0);
}

t_list **general_parser(t_list **list__to_track, int f(char **,t_list **),
	void (*destructor)(t_list **))
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
        {
            if(destructor && *result)
                destructor(result);
            else
                free(result);
            return(NULL);
        }
        if(f(actual_node->content, result) == -1)
        {
            if(destructor && *result)
                destructor(result);
            else
                free(result);
            return(NULL);
        }
        actual_node = actual_node->next;
    }
    if(result && *result == NULL)
        return(free(result), NULL);
    return(result);
}
