/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:15:12 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 04:06:04 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "../src/aux_libft/include/libft.h"
# include "../linux-minilibx/mlx.h"
# include "parser.h"

/* =[ Primitive Scene ]===================================================== */
// Raw parsed data before conversion to final scene structures

typedef struct primitive_escene_s
{
	t_list			**object;
	t_list			**light;
	t_list			**al;
	t_list			**camera;
}					t_primitive_escene;

/* =[ Validation Functions ]================================================ */

bool				if_betwen_values(float elem, float min, float max);
size_t				double_array_len(char **doble);
bool				str_empty(char *str);
bool				correct_number_of_elements(char **element);
int					ft_ispace(char c);

/* =[ Float List Parsing ]================================================== */

t_list				**list_of_float_checker(char **split, float max, float min, bool rng);						// line break to pass norminette - [ 42 ]

/* =[ Element Parsers ]===================================================== */

int					ambient_light_parser(char **elem, t_list **list);
int					light_parser(char **elem, t_list **list);
int					camera_parser(char **elem, t_list **list);
int					object_parser(char **elem, t_list **list);
t_list				**general_parser(t_list **list, int f(char **, t_list **), void (*destructor)(t_list **));	// line break to pass norminette - [ 42 ]

/* =[ File Parsing ]======================================================== */

char				*parser_file_name(char *file);
char				*parser_texture_name(char *file);

/* =[ Primitive Scene Functions ]=========================================== */

t_primitive_escene	*escene_primiteve_contructor(char *file);
void				escene_primitive_destructor(t_primitive_escene *prim);
int					primitive_escene_t_asignation(t_list **el, t_primitive_escene *s);							// line break to pass norminette - [ 42 ]
t_list				**get_list_of_elements(t_primitive_escene *prim, enum e_type_list id);						// line break to pass norminette - [ 42 ]

/* =[ Memory Cleanup ]====================================================== */

void				free_double_pointer(char **ptr);
void				free_list_of_floats(t_list **list);
void				free_al_primitive(t_list **list);
void				free_primitive_light(t_list **list);
void				free_list_of_lights_primitive(t_list **list);
void				free_list_camera_primitive(t_list **list);
void				primitive_sphere_destructor(t_list **list);
void				primitive_plane_destructor(t_list **list);
void				primitive_cylinder_destructor(t_list **list);
void				primitive_destructor_selector(t_list **list, char *id);
void				list_of_objects_destructor_primitive(t_list **list);

/* =[ Debug Functions ]===================================================== */

void				print_primitive_escene(t_primitive_escene *escene);

#endif
