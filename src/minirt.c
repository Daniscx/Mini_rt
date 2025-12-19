/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:30:47 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/19 19:50:27 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	error_manager(char *error_message)
{
	if (!error_message)
		exit(1);
	ft_putstr_fd("\033[1;36mminiRT: \033[1;31mError: \033[0m", STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(1);
}

static void	parse_window_size(t_minirt *rt, int argc, char **argv)
{
	rt->win_w = WIDTH_LOW;
	rt->win_h = HEIGHT_LOW;
	if (argc >= 4)
	{
		rt->win_w = ft_atoi(argv[2]);
		rt->win_h = ft_atoi(argv[3]);
		if (rt->win_w < 426 || rt->win_w > 4096)
		{
			printf("\033[0;31mInvalid width.\033[0m Using default: %i\n", WIDTH_LOW);
			rt->win_w = WIDTH_LOW;
		}
		if (rt->win_h < 240 || rt->win_h > 2160)
		{
			printf("\033[0;31mInvalid height.\033[0m Using default: %i\n", HEIGHT_LOW);
			rt->win_h = HEIGHT_LOW;
		}
	}
}

static void	print_usage(void)
{
	ft_putstr_fd("make <mode>", 1);
	ft_putstr_fd("Usage: ./miniRT <scene.rt> [width] [height]\n", 1);
	ft_putstr_fd("  scene.rt		- Scene file to load\n", 1);
	ft_putstr_fd("  width			- Window width (426-4096) [optional]\n", 1);
	ft_putstr_fd("  height			- Window height (240-2160) [optional]\n", 1);
	ft_putstr_fd("  color bleeding	- Compile using \"make cb\" to use color bleeding mode. [optional]\n", 1);
}

int	main(int argc, char **argv)
{
	t_minirt	rt;
	int			route;

	if (argc < 2 || argc > 4 || (COLOR_BLEEDING != 0 && COLOR_BLEEDING != 1))
	{
		print_usage();
		return (1);
	}
	route = parser_file_name(argv[1]);
	ft_bzero(&rt, sizeof(t_minirt));
	parse_window_size(&rt, argc, argv);
	if (scene_load(&rt.scene, argv[1], route) < 0)
		error_manager("Failed to load scene file.");
	minirt_init(&rt);
	render_scene(&rt);
	mlx_loop(rt.mlx);
	minirt_cleanup(&rt);
	return (0);
}
