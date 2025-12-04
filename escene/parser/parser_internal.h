/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:15:12 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/03 23:51:19 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_INTERNAL_H
#define PARSER_INTERNAL_H

#include "../../libft/libft.h"
#include "../parser.h"
typedef struct primitve_escene_s
{
    t_list **object;
    t_list **light;
    t_list **al;
    t_list **camera;
} primitive_escene_t;

#endif