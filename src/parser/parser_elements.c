/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 17:14:48 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/parser_internal.h"
# include "../../includes/minirt.h"

int ambient_light_parser(char **actual_element, t_list **list_to_add_element, int line, t_error_list *errors)
{
    int     i;
    char    **rgb_to_split;
    float   *actual_float;
    t_list  **list_float;

    i = 1;
    if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) == 0 && *list_to_add_element)
        return (error_list_add(errors, line, "Multiple ambient light declarations detected.", "A"), -1);
    else if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) != 0)
        return (0);
    while(actual_element[1][i])
    {
        if(ft_isdigit(actual_element[1][i]) == 0 && actual_element[1][i] != '.')
        {
            error_list_add(errors, line, "Invalid numeric value.", "ratio");
            return (-1);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[1]);
    if(if_betwen_values(*actual_float, 0,  1) == false)
    {
        free(actual_float);
        return(error_list_add(errors, line, "Value must be between 0.0 and 1.0.", "ratio"), -1);
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
    rgb_to_split = ft_split(actual_element[2], ',');
    list_float = list_of_float_checker(rgb_to_split, 255 , 0, true, line, errors, "color");
    free_double_pointer(rgb_to_split);
    if(!list_float)
        return(-1);
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    return(0);
}

int light_parser(char **actual_element, t_list **list_to_add_element, int line, t_error_list *errors)
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
        return (error_list_add(errors, line, "Invalid position format.", "position"), free(new_light_element), -1);
    list_float = list_of_float_checker(splited_element, 0, 0, false, line, errors, "position");
    free_double_pointer(splited_element);
    if(!list_float)
        return(free(new_light_element), -1);
    ft_lstadd_front(new_light_element, ft_lstnew(list_float));
    while(actual_element[2][i])
    {
        if(ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
        {
            error_list_add(errors, line, "Invalid numeric value.", "brightness");
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
        return(error_list_add(errors, line, "Value must be between 0.0 and 1.0.", "brightness"), -1);
    }
    ft_lstadd_back(new_light_element, ft_lstnew(actual_float));
    if(!actual_element[3])
        actual_element[3] = ft_strdup("255,255,255");
    splited_element = ft_split(actual_element[3], ',');
    if(!splited_element || *splited_element == NULL)
    {
        free_primitive_light(new_light_element);
        error_list_add(errors, line, "Invalid color format.", "color");
        return(-1);
    }
    list_float = list_of_float_checker(splited_element, 255 , 0, true, line, errors, "color");
    free_double_pointer(splited_element);
    if(!list_float)
    {
        free_primitive_light(new_light_element);
        return(-1);
    }
    ft_lstadd_back(new_light_element, ft_lstnew(list_float));
    ft_lstadd_back(list_to_add_element, ft_lstnew(new_light_element));
    return(0);
}

int camera_parser(char **actual_element, t_list **list_to_add_element, int line, t_error_list *errors)
{
    int i;
    char **x_y_z_to_split;
    float *actual_float;
    t_list **list_float;

    i = 0;
    if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) == 0 && *list_to_add_element)
        return(error_list_add(errors, line, "Multiple camera declarations detected.", "C"), -1);
    else if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) != 0)
        return (0);
    x_y_z_to_split = ft_split(actual_element[1], ',');
    list_float = list_of_float_checker(x_y_z_to_split, 0 , 0, false, line, errors, "position");
    free_double_pointer(x_y_z_to_split);
    if(!list_float)
        return(-1);
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    x_y_z_to_split = ft_split(actual_element[2], ',');
    list_float = list_of_float_checker(x_y_z_to_split, 0 , 0, false, line, errors, "orientation");
    free_double_pointer(x_y_z_to_split);
    if(!list_float)
        return(-1);
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    i = 0;
    if(actual_element[3][i] == '-')
        i++;
    while(actual_element[3][i])
    {
        if(ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
        {
            error_list_add(errors, line, "Invalid numeric value.", "FOV");
            return(-1);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[3]);
    if(if_betwen_values(*actual_float, 0, 180) == false)
    {
        free(actual_float);
        return(error_list_add(errors, line, "Value must be between 0 and 180.", "FOV"), -1);
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
    return (0);
}

static t_list **sphere_parser(char **actual_element, int line, t_error_list *errors)
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
    float_list = list_of_float_checker(element_splited, 0, 0, false, line, errors, "position");
    free_double_pointer(element_splited);
    if(!float_list)
        return(primitive_sphere_destructor(result), NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    i = 0;
    if(actual_element[2][i] == '-')
        i++;
    while(actual_element[2][i])
    {
        if(ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
        {
            error_list_add(errors, line, "Invalid numeric value.", "diameter");
            return(primitive_sphere_destructor(result), NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[2]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    element_splited = ft_split(actual_element[3], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true, line, errors, "color");
    free_double_pointer(element_splited);
    if(!float_list)
        return(primitive_sphere_destructor(result), NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    if(actual_element[4])
    {
        texture = parser_texture_name(actual_element[4]);
        if(texture == NULL)
        {
            error_list_add(errors, line, "Texture file does not exist.", "texture");
            return(primitive_sphere_destructor(result), NULL);
        }
        ft_lstadd_back(result, ft_lstnew(texture));
        if(actual_element[5])
        {
            texture = parser_texture_name(actual_element[5]);
            if(texture == NULL)
            {
                error_list_add(errors, line, "Texture file does not exist.", "normal_map");
                return(primitive_sphere_destructor(result), NULL);
            }
            ft_lstadd_back(result, ft_lstnew(texture));
        }
    }
    return(result);
}

static t_list **plane_parser(char **actual_element, int line, t_error_list *errors)
{
    t_list **result;
    t_list **float_list;
    char **element_splited;

    result = ft_calloc(1, sizeof(t_list *));
    ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
    element_splited = ft_split(actual_element[1], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false, line, errors, "position");
    free_double_pointer(element_splited);
    if(!float_list)
        return(primitive_plane_destructor(result), NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[2], ',');
    float_list = list_of_float_checker(element_splited, 1, -1, true, line, errors, "normal");
    free_double_pointer(element_splited);
    if(!float_list)
        return(primitive_plane_destructor(result), NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[3], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true, line, errors, "color");
    free_double_pointer(element_splited);
    if(!float_list)
        return(primitive_plane_destructor(result), NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    return(result);
}

static t_list **cylinder_parser(char **actual_element, int line, t_error_list *errors)
{
    t_list **result;
    t_list **float_list;
    char **element_splited;
    int i;
    float   *actual_float;

    result = ft_calloc(1, sizeof(t_list *));
    ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
    element_splited = ft_split(actual_element[1], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false, line, errors, "position");
    free_double_pointer(element_splited);
    if(!float_list)
        return(primitive_cylinder_destructor(result), NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[2], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false, line, errors, "axis");
    free_double_pointer(element_splited);
    if(!float_list)
        return(primitive_cylinder_destructor(result), NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    i = 0;
    if(actual_element[3][i] == '-')
        i++;
    while(actual_element[3][i])
    {
        if(ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
        {
            error_list_add(errors, line, "Invalid numeric value.", "diameter");
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
            error_list_add(errors, line, "Invalid numeric value.", "height");
            return(primitive_cylinder_destructor(result), NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_atof(actual_element[4]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    element_splited = ft_split(actual_element[5], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true, line, errors, "color");
    free_double_pointer(element_splited);
    if(!float_list)
        return(primitive_cylinder_destructor(result), NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    return(result);
}

int object_parser(char **actual_element, t_list **list_to_add_element, int line, t_error_list *errors)
{
    size_t len;
    t_list **result;

    len = ft_strlen(actual_element[0]);
    if(ft_strncmp(actual_element[0], "sp", len) == 0 || ft_strncmp(actual_element[0], "spt", len) == 0)
    {
        result = sphere_parser(actual_element, line, errors);
        if(!result)
            return(-1);
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
        if(ft_strncmp(actual_element[0], "pl", len) == 0 || ft_strncmp(actual_element[0], "plc", len) == 0 )
    {
        result = plane_parser(actual_element, line, errors);
        if(!result)
            return(-1);
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
    if(ft_strncmp(actual_element[0], "cy", len) == 0 || ft_strncmp(actual_element[0], "co", len) == 0)
    {
        result = cylinder_parser(actual_element, line, errors);
        if(!result)
            return(-1);
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
    return(0);
}

t_list **general_parser(t_list **list__to_track, t_parser_func f, void (*destructor)(t_list **))
{
    t_list **result;
    t_list *actual_node;
    t_line_data *line_data;
    t_error_list *errors;
    int has_errors;

    if(!list__to_track || *list__to_track == NULL)
        return(NULL);
    result = ft_calloc(1, sizeof(t_list *));
    errors = error_list_create();
    actual_node = *list__to_track;
    has_errors = 0;
    while(actual_node)
    {
        line_data = (t_line_data *)actual_node->content;
        if(correct_number_of_elements(line_data->content, line_data->line_number, errors) == false)
            has_errors = 1;
        else if(f(line_data->content, result, line_data->line_number, errors) == -1)
            has_errors = 1;
        actual_node = actual_node->next;
    }
    if(has_errors)
    {
        error_list_print(errors);
        error_list_free(errors);
        if(destructor && *result)
            destructor(result);
        else
            free(result);
        return(NULL);
    }
    error_list_free(errors);
    if(result && *result == NULL)
        return(free(result), NULL);
    return(result);
}
