/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:30:30 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/10 20:15:19 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
//INICIO del debuger de primitive 
void print_primitive_escene(primitive_escene_t *escene)
{
    t_list *aux;
    t_list *sub;
    aux = *escene->al;
    printf("%f\n", *(float *)aux->content);
    aux = aux->next;
    sub = *(t_list **)aux->content;
    while(sub)
    {
        printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
}