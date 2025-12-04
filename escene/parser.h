/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:13:55 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/04 14:33:19 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H 
#define PARSER_H
//declaracion de la estructura para que asi se pueda llamar 
//fuera del modulo pero no acceder a sus contenidos directamente
typedef struct escene_primitive_s escene_primitive_t;
//constructor de la estructura aqui es donde con listas se asignar precariamente los valores
//luego a traves de esa estructura se concretara la final
escene_primitive_t *escene_primiteve_contructor(char *file);
//destructor no tiene mucho misterio
void *escene_primiteve_destructor(escene_primitive_t * escene);

#endif