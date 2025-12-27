/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:43:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/27 17:35:52 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objects.h"

t_paraboid *paraboid_constructor(t_list **components, t_object *object)
{
    t_list *aux;
    t_paraboid *result;
    
    aux = *components;
    result = ft_calloc(1, sizeof(t_paraboid ));
    result->vertex = vector_constructor((t_list **)aux->content, false);
    aux = aux->next;
    result->axis = vector_constructor((t_list **)aux->content, false);
    aux = aux->next;
    result->a = *(float *)aux->content;
    aux = aux->next;
    result->color = vector_constructor((t_list **)aux->content, true);
    object->collision = NULL; // funcion de colision
    object->check_board = false;
    object->intersecction = NULL; // funcion de hit
    object->movement = NULL; // FUNCION de move
    object->postion = NULL; //funcion conseguir el centro
    return(result);
 }
 