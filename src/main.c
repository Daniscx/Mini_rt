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

void	error_manager(char *error_message)
{
	if (!error_message)
		exit(1);
	write(2, "Error\n", 6);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	exit(1);
}

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
	return (0);
}

