/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:13:55 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 14:47:03 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdbool.h"
#ifndef PARSER_H 
#define PARSER_H

/* Opaque pointer to primitive scene structure - hides implementation details */
typedef struct primitive_escene_s t_primitive_escene;
typedef struct s_list t_list;

/* Enumeration for element types in scene */
enum type_list
{
    AL,  /* Ambient Light */
    L,   /* Light source */
    OB,  /* Object */
    C,   /* Camera */
};

/* Load and parse scene file, return primitive scene structure */
t_primitive_escene *escene_primiteve_contructor(char *file);

/* Deallocate entire scene structure and its contents */
void escene_primitive_destructor(t_primitive_escene *primitive);

/* Check if value is within specified range */
bool if_betwen_values(float element_to_check, float minmun_value, float maximun_value);

/* Retrieve specific element list from parsed scene */
t_list **get_list_of_elements(t_primitive_escene *primitive, enum type_list identifcator);

#endif