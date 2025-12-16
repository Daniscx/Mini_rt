/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:30:47 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 10:45:37 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
** Prints error message to stderr and exits the program with failure status.
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
** Program entry point. Loads scene, initializes graphics and starts loop.
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
