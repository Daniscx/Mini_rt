/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:49:37 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/10 11:56:14 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/mini_rt.h"
#include "escene/parser.h"
//funcion inicial para gestionar error es precaria 
//TO DO: gestionar la liberacion de memoria en cada caso luego añadir el Error|\n
void error_manager(char *error_message)
{
    if(!error_message)
        exit(1);
    write(2, error_message, ft_strlen(error_message));
    exit(1);
}
//main que utilice para probar mi conversor a float funciona pero hay que checkear algun caso especifico
int main(int args , char **argv)
{
    if(args != 2)
        error_manager("Check the amount of args");
    escene_primiteve_contructor(argv[1]);
    return(1);
}