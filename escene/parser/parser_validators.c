/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 17:59:50 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "parser_internal.h"
#include "stdbool.h"
#include "../../includes/mini_rt.h"

/**
 * Checks if a value is between a minimum and maximum range
 * @param element_to_check The value to check
 * @param minmun_value Minimum allowed value
 * @param maximun_value Maximum allowed value
 * @return true if value is within range, false otherwise
 */
bool if_betwen_values(float element_to_check, float minmun_value , float maximun_value)
{
    if(element_to_check > maximun_value || element_to_check < minmun_value)
        return(false);
    return(true);
}

/**
 * Returns the length of a null-terminated array of strings
 * @param doble Array of strings to measure
 * @return Number of elements in the array (0 if NULL)
 */
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

/**
 * Checks if a string contains only whitespace characters
 * @param str String to check
 * @return true if string is empty or only whitespace, false otherwise
 */
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

/**
 * Validates that an element has the correct number of arguments
 * Different elements require different argument counts:
 * - C, pl, sp, plc: 3 arguments
 * - L: 2 or 3 arguments
 * - A: 2 arguments
 * - cy, co, spt: 5 arguments
 * @param element Array of arguments, first element is the identifier
 * @return true if correct number of arguments, false otherwise
 */
bool correct_number_of_elements(char **element)
{
    size_t nb_of_args;
    size_t len;
    if (!element || !element[0])
        return (false);
    len = ft_strlen(element[0]);
    nb_of_args = double_array_len(element + 1);
    
    if( ft_strncmp(element[0], "C", len) == 0|| ft_strncmp(element[0], "pl", len) == 0 
        || ft_strncmp(element[0], "sp", len) == 0 || ft_strncmp(element[0], "plc", len) == 0)
    {
        if(nb_of_args == 3)
            return(true);
        else
            return(false);
    }
    else if(ft_strncmp(element[0], "L", len) == 0 && (nb_of_args == 2 || nb_of_args == 3))
        return(true);
    else if(ft_strncmp(element[0], "A", len) == 0  && nb_of_args == 2 )
        return(true);
    else if ((ft_strncmp(element[0], "cy", len) == 0 || ft_strncmp(element[0], "co", len) == 0 || ft_strncmp(element[0], "spt", len) == 0)
                 && nb_of_args ==  5)
        return(true);
    else
    {
        error_manager("the file .rt contain incorrect elements ,please correct them", false);
         return(false);
    }
       
}

/**
 * Generic validator that creates a list of floats from an array of string numbers
 * Validates that there are exactly 3 elements and converts them to floats
 * Optionally checks if values are within a specified range
 * @param splited_element Array of 3 strings representing numbers
 * @param max Maximum allowed value (range check disabled if max=0 and min=0)
 * @param min Minimum allowed value
 * @param range If true, performs range validation
 * @return Pointer to newly allocated list of floats, NULL on error
 */
t_list **list_of_float_checker(char **splited_element, float max  , float min, bool range)
{
    t_list **resuslt;
    int i;
    int j;
    float *actual_float;
    if(double_array_len(splited_element) != 3)
        return(error_manager("no valid parametter find in :", false), NULL);
    j = 0; 
    i = 0;
    resuslt = ft_calloc(1, sizeof(t_list *));
    while(splited_element[j])
    {
        if(splited_element[j][i] == '-')
            i++;
        while(splited_element[j][i])
        { 
            if(ft_isdigit(splited_element[j][i]) == 0 && splited_element[j][i] != '.')
            {
                error_manager("no valid parametter find in :", false);
                return(NULL);
            }
            i++;
        }
        i = 0;
        actual_float = ft_calloc(1, sizeof(float));
         *actual_float = ft_float(splited_element[j]); 
         if(if_betwen_values(*actual_float, min, max) == false && range == true)
         {
            error_manager("no valid parametter find in :", false);
            return(NULL);  
         }
            
        ft_lstadd_back(resuslt, ft_lstnew(actual_float));
        j++;
    }
    return(resuslt);
}

/**
 * Checks if a character is a whitespace character
 * @param c Character to check
 * @return 1 if whitespace, 0 otherwise
 */
int	ft_ispace(char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}
