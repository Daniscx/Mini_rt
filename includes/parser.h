/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:13:55 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:44:23 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../src/aux_libft/include/libft.h"
# include "../linux-minilibx/mlx.h"

/* =[ Forward Declarations ]================================================ */

typedef struct primitive_escene_s	t_primitive_escene;
typedef struct s_list				t_list;

/* =[ Parser Element Types ]================================================ */

enum e_type_list
{
	AL,
	L,
	OB,
	C,
};

/* =[ Parser Functions ]==================================================== */

t_primitive_escene	*escene_primiteve_constructor(char *file, int *msg);
void				escene_primitive_destructor(t_primitive_escene *primitive);

/* =[ Parser Utilities ]==================================================== */

bool				if_betwen_values(float elem, float min, float max);
t_list				**get_list_of_elements(t_primitive_escene *prim,
						enum e_type_list id);

/* ========================================================================= */

#endif
