/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:13:55 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/10 19:30:06 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdbool.h"
#ifndef PARSER_H 
#define PARSER_H
//declaracion de la estructura para que asi se pueda llamar 
//fuera del modulo pero no acceder a sus contenidos directamente
typedef struct primitive_escene_s primitive_escene_t;
//constructor de la estructura aqui es donde con listas se asignar precariamente los valores
//luego a traves de esa estructura se concretara la final
primitive_escene_t *escene_primiteve_contructor(char *file);
//destructor no tiene mucho misterio
void *escene_primiteve_destructor(primitive_escene_t * escene);
bool if_betwen_values(float element_to_check, float minmun_value , float maximun_value);

#endif