/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:15:12 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:45:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "../src/aux_libft/include/libft.h"
# include "../linux-minilibx/mlx.h"
# include "parser.h"

/* =[ Error Tracking ]====================================================== */

typedef struct s_parse_error
{
	int						line;
	char					*message;
	char					*parameter;
	struct s_parse_error	*next;
}	t_parse_error;

typedef struct s_error_list
{
	t_parse_error	*first;
	t_parse_error	*last;
	int				count;
}	t_error_list;

/* =[ Float Check Context ]================================================= */

typedef struct s_float_ctx
{
	float			max;
	float			min;
	bool			range;
	int				line;
	t_error_list	*errors;
	char			*param;
}	t_float_ctx;

/* =[ Line Data ]=========================================================== */

typedef struct s_line_data
{
	int		line_number;
	char	**content;
}	t_line_data;

/* =[ Primitive Scene ]===================================================== */

typedef struct primitive_escene_s
{
	t_list			**object;
	t_list			**light;
	t_list			**al;
	t_list			**camera;
}					t_primitive_escene;

/* =[ Error Management ]=================================================== */

t_error_list		*error_list_create(void);
void				error_list_add(t_error_list *list, int line, char *msg,
						char *param);
void				error_list_print(t_error_list *list);
void				error_list_free(t_error_list *list);

/* =[ Validation Functions ]================================================ */

bool				if_betwen_values(float elem, float min, float max);
size_t				double_array_len(char **doble);
bool				str_empty(char *str);
bool				correct_number_of_elements(char **element, int line,
						t_error_list *errors);
int					ft_ispace(char c);

/* =[ Float List Parsing ]================================================== */

t_list				**list_of_float_checker(char **split, t_float_ctx *ctx);

/* =[ Element Parsers ]===================================================== */

int					ambient_light_parser(char **elem, t_list **list, int line,
						t_error_list *errors);
int					light_parser(char **elem, t_list **list, int line,
						t_error_list *errors);
int					camera_parser(char **elem, t_list **list, int line,
						t_error_list *errors);
int					object_parser(char **elem, t_list **list, int line,
						t_error_list *errors);

/* =[ Object Parsers ]====================================================== */

t_list				**sphere_parser(char **elem, int line, t_error_list *e);
t_list				**plane_parser(char **elem, int line, t_error_list *e);
t_list				**cylinder_parser(char **elem, int line, t_error_list *e);
typedef int			(*t_parser_func)(char **, t_list **, int, t_error_list *);
t_list				**general_parser(t_list **list, t_parser_func f,
						void (*destructor)(t_list **));

/* =[ File Parsing ]======================================================== */

char				*parser_file_name(char *file);
char				*parser_texture_name(char *file);

/* =[ Primitive Scene Functions ]=========================================== */

t_primitive_escene	*escene_primiteve_constructor(char *file, int *msg);
void				escene_primitive_destructor(t_primitive_escene *prim);
int					primitive_escene_t_asignation(t_list **el,
						t_primitive_escene *s);
t_list				**get_list_of_elements(t_primitive_escene *prim,
						enum e_type_list id);

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

/* ========================================================================= */

#endif
