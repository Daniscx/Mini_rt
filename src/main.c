/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:30:47 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:30:48 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/*
** Maneja errores mostrando un mensaje y terminando el programa
** Parámetros:
**   - error_message: mensaje de error a mostrar
** Comportamiento:
**   - Imprime "Error\n" en stderr
**   - Imprime el mensaje de error en stderr
**   - Sale del programa con exit(1)
** NOTA: Si error_message es NULL, sale sin mostrar mensaje
*/
void	error_manager(char *error_message)
{
	if (!error_message)
		exit(1);
	write(2, "Error\n", 6);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	exit(1);
}

/*
** Función principal del programa miniRT
** Parámetros:
**   - argc: número de argumentos
**   - argv: array de argumentos (argv[1] = archivo.rt)
** Flujo del programa:
**   1. Valida argumentos (debe ser exactamente 2)
**   2. Inicializa estructura t_minirt a cero
**   3. Parsea el archivo .rt con escene_constructor
**   4. Inicializa MLX, ventana e imagen
**   5. Renderiza la escena
**   6. Entra en el loop de eventos de MLX
**   7. Limpia memoria al salir (nunca llega aquí por mlx_loop)
** Retorna:
**   - 0 si todo OK (nunca alcanzado debido a mlx_loop)
*/
int	main(int argc, char **argv)
{
	t_minirt	rt;

	if (argc != 2)
		error_manager("Usage: ./miniRT <scene.rt>");
	ft_bzero(&rt, sizeof(t_minirt));
	rt.scene = escene_constructor(argv[1]);
	if (!rt.scene)
		error_manager("Failed to parse scene file");
	minirt_init(&rt);
	render_scene(&rt);
	mlx_loop(rt.mlx);
	minirt_cleanup(&rt);
	return (0);
}

