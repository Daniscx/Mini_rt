/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:30:47 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 01:37:51 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
** Handles errors by displaying a message and terminating the program.
** Parameters:
**   - error_message: error message to display
** Behavior:
**   - Prints the error message to stderr
**   - Exits the program with exit(1)
** Note: If error_message is NULL, exits without displaying message
*/
void	error_manager(char *error_message)
{
	if (!error_message)
		exit(1);
	ft_putstr_fd("\033[36mminiRT\033[0m: \033[1m\033[31mError\033[0m: ", STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(1);
}

/*
** Main function of the miniRT program.
** Parameters:
**   - argc: number of arguments
**   - argv: array of arguments (argv[1] = scene.rt file)
** Program flow:
**   1. Validates arguments (must be exactly 2)
**   2. Initializes t_minirt structure to zero
**   3. Parses the .rt file with scene_load
**   4. Initializes MLX, window and images
**   5. Renders the scene
**   6. Enters the MLX event loop
**   7. Cleans up memory on exit (never reached due to mlx_loop)
** Returns:
**   - 0 if successful (never reached due to mlx_loop)
*/
int	main(int argc, char **argv)
{
	t_minirt	rt;
	int			route;

	if (argc != 2)
		error_manager("Please do \"./miniRT <scene.rt>\"!");
	route = parser_file_name(argv[1]);
	ft_bzero(&rt, sizeof(t_minirt));
	if (scene_load(&rt.scene, argv[1], route) < 0)
		error_manager("Failed to load scene file.");
	minirt_init(&rt);
	render_scene(&rt);
	mlx_loop(rt.mlx);
	minirt_cleanup(&rt);
	return (0);
}
