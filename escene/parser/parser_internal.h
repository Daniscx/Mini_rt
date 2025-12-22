/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:15:12 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 18:50:53 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_INTERNAL_H
#define PARSER_INTERNAL_H

#include "../../libft/libft.h"
#include "../parser.h"
#include "stdio.h"
#include "fcntl.h"
#include "unistd.h"

typedef struct primitive_escene_s
{
    t_list **object;
    t_list **light;
    t_list **al;
    t_list **camera;
} t_primitive_escene;

/* parser_validators.c - Input validation functions */
bool if_betwen_values(float element_to_check, float minmun_value, float maximun_value); /* Check if float is within range */
size_t double_array_len(char **doble); /* Count null-terminated string array length */
bool str_empty(char *str); /* Check if string contains only whitespace */
bool correct_number_of_elements(char **element); /* Validate argument count for scene elements */
t_list **list_of_float_checker(char **splited_element, float max, float min, bool range); /* Parse and validate float array */
int ft_ispace(char c); /* Check if character is whitespace */

/* parser_elements.c - Scene element parsers */
int ambient_light_parser(char **actual_element, t_list **list_to_add_element); /* Parse ambient light (A) */
int  light_parser(char **actual_element, t_list **list_to_add_element); /* Parse light source (L) */
int  camera_parser(char **actual_element, t_list **list_to_add_element); /* Parse camera (C) */
int object_parser(char **actual_element, t_list **list_to_add_element); /* Parse object (sp, pl, cy, co) */
t_list **general_parser(t_list **list__to_track, int f(char **, t_list **)); /* Generic dispatcher for all elements */

/* parser_file.c - File handling functions */
char *parser_file_name(char *file); /* Resolve .rt filename from user input */
t_primitive_escene *escene_primiteve_contructor(char *file); /* Load and parse entire scene file */
char 	*parser_texture_name(char *file);

/* parser_assignment.c - Data organization functions */
int primitive_escene_t_asignation(t_list **element_to_conver, t_primitive_escene *struct_to_assignate); /* Organize parsed lists into scene struct */
t_list **get_list_of_elements(t_primitive_escene *primitive, enum type_list identifcator); /* Retrieve specific element list from scene */

/* parser_destructors.c - Memory deallocation functions */
void free_list_of_floats(t_list **list); /* Deallocate float value list */
void free_al_primitive(t_list **list); /* Free ambient light structure */
void free_primitive_light(t_list **list); /* Free single light element */
void free_list_of_lights_primitive(t_list **list); /* Free all light elements */
void free_list_camera_primitive(t_list **list); /* Free camera structure */
void primitive_sphere_destructor(t_list **list); /* Free sphere object data */
void primitive_plane_destructor(t_list **list); /* Free plane object data */
void primitive_cylinder_destructor(t_list **list); /* Free cylinder object data */
void primitive_destructor_selector(t_list **list, char *identificator); /* Type-based destructor dispatcher */
void list_of_objects_destructor_primitive(t_list **list); /* Free all object elements */
void escene_primitive_destructor(t_primitive_escene *primitive); /* Free entire scene structure */

/* parser_internal utilities (from old parsing.c) */
void print_primitive_escene(t_primitive_escene *escene); /* Debug: print scene contents */

#endif