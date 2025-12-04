/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escene_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:56:46 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/04 14:50:01 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESCENE_INTERNAL_H
#define ESCENE_INTERNAL_H

#include "../includes/escene.h"
//el parseo se hara dentro del modulo como un submodulo dentro de este, se hace asi
// para crear el menor numero de dependencias posible
#include "parser.h"
#include "../libft/libft.h"
//en este es el internal todavia no hay declarada ninguna funcion aqui pero servira para unir los distintos .c del modulo



//estructura que entrega el constructor dos lista enlazadas una siendo para objetos la cual el contenido de cada nodo sera la estructura del objeto en cuestion
//la luz tambien es una lista por cuestion del bonus "multiples focos de luz"
//TO:DO crear estructura especifica para la cada una de la parte de la estructura
// par esto se necesita crear el modulo rgb light, y objetos a parte de , camara vectores y coordendas se puede hacer estos 2 ultimos en el mismo ya que practicamente comparten valores
// solo es necesario hacer los constructores de las estructuras nada mas lo demas se puede hacer mas adelante
//a parte algo importante no se si quieres añadir en esta estructura  una para lo necesario par el mlx o hacerlo separado 
typedef struct escene_s
{
    t_list **object;
    t_list **light;
    void   *al;
    void   *camera;
};
//structura que entreagara el parser para crear la final;



#endif