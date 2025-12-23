/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:42:18 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/parser_internal.h"
# include "../../includes/minirt.h"

bool if_betwen_values(float element_to_check, float minmun_value , float maximun_value)
{
    if(element_to_check > maximun_value || element_to_check < minmun_value)
        return(false);
    return(true);
}

size_t double_array_len(char **doble)
{
    size_t j;
    if (!doble || !*doble)
        return (0);
    j = 0;
    while (doble[j] != NULL)
        j++;
    return (j);
}

bool str_empty(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(ft_ispace(str[i]) == 0)
            return(false);
        i++;
    }
    return(true);
}

bool correct_number_of_elements(char **element, int line, t_error_list *errors)
{
    size_t nb_of_args;
    size_t len;
    if (!element || !element[0])
        return (error_list_add(errors, line, "Empty or invalid line.", NULL), false);
    len = ft_strlen(element[0]);
    nb_of_args = double_array_len(element + 1);
    if( ft_strncmp(element[0], "C", len) == 0|| ft_strncmp(element[0], "pl", len) == 0 || ft_strncmp(element[0], "sp", len) == 0 || ft_strncmp(element[0], "plc", len) == 0)
    {
        if(nb_of_args == 3)
            return(true);
        else
            return(error_list_add(errors, line, "Expected 3 arguments.", element[0]), false);
    }
    else if(ft_strncmp(element[0], "L", len) == 0 && (nb_of_args == 2 || nb_of_args == 3))
        return(true);
    else if(ft_strncmp(element[0], "L", len) == 0)
        return(error_list_add(errors, line, "Expected 2 or 3 arguments.", element[0]), false);
    else if(ft_strncmp(element[0], "A", len) == 0  && nb_of_args == 2 )
        return(true);
    else if(ft_strncmp(element[0], "A", len) == 0)
        return(error_list_add(errors, line, "Expected 2 arguments.", element[0]), false);
    else if ((ft_strncmp(element[0], "cy", len) == 0 || ft_strncmp(element[0], "co", len) == 0 || ft_strncmp(element[0], "spt", len) == 0) && nb_of_args ==  5)
        return(true);
    else if (ft_strncmp(element[0], "cy", len) == 0 || ft_strncmp(element[0], "co", len) == 0 || ft_strncmp(element[0], "spt", len) == 0)
        return(error_list_add(errors, line, "Expected 5 arguments.", element[0]), false);
    else
    {
        error_list_add(errors, line, "Unknown element type.", element[0]);
        return(false);
    }
}

t_list **list_of_float_checker(char **splited_element, float max  , float min, bool range, int line, t_error_list *errors, char *param_name)
{
    t_list **result;
    int i;
    int j;
    float *actual_float;

    if(double_array_len(splited_element) != 3)
        return(error_list_add(errors, line, "Expected 3 comma-separated values.", param_name), NULL);
    j = 0;
    i = 0;
    result = ft_calloc(1, sizeof(t_list *));
    while(splited_element[j])
    {
        if(splited_element[j][i] == '-')
            i++;
        while(splited_element[j][i])
        {
            if(ft_isdigit(splited_element[j][i]) == 0 && splited_element[j][i] != '.')
            {
                error_list_add(errors, line, "Invalid numeric value.", param_name);
                free_list_of_floats(result);
                return(NULL);
            }
            i++;
        }
        i = 0;
        actual_float = ft_calloc(1, sizeof(float));
        *actual_float = ft_atof(splited_element[j]);
        if(if_betwen_values(*actual_float, min, max) == false && range == true)
        {
            error_list_add(errors, line, "Value out of allowed range.", param_name);
            free(actual_float);
            free_list_of_floats(result);
            return(NULL);
        }
        ft_lstadd_back(result, ft_lstnew(actual_float));
        j++;
    }
    return(result);
}

int	ft_ispace(char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}
