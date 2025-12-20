/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:07:23 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 17:19:06 by ravazque         ###   ########.fr       */
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
	rt->frame_rate = TARGET_FPS;
	if (argc >= 4)
	{
		rt->win_w = ft_atoi(argv[2]);
		rt->win_h = ft_atoi(argv[3]);
		if (argc >= 5)
			rt->frame_rate = ft_atoi(argv[4]);
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
		if (rt->frame_rate < 24 || rt->frame_rate > 60)
		{
			printf("\033[0;31mInvalid frame rate.\033[0m Using default: %i\n", TARGET_FPS);
			rt->frame_rate = TARGET_FPS;
		}
	}
}

static void	print_usage(void)
{
	ft_putstr_fd("\n\033[38;5;208mCompile with: \033[0m\"make cb\" to use the color bleeding mode.\n", 1);
	ft_putstr_fd("\033[36mUsage: \033[0m./miniRT <scene.rt> [width] [height] [fps]\n", 1);
	ft_putstr_fd("  scene.rt        - Scene file to load.\n", 1);
	ft_putstr_fd("  width           - Window width.      (426-4096) [optional]\n", 1);
	ft_putstr_fd("  height          - Window height.     (240-2160) [optional]\n", 1);
	ft_putstr_fd("  maximum FPS     - Frames per second. (24-60)    [optional]\n", 1);
	ft_putstr_fd("\033[92m\n// - If you want to define the width and height of the window, you must\n// enter at least those two parameters.", 1);
	ft_putstr_fd("\n// - Only once the width and height have been defined can the maximum FPS\n// be defined.", 1);
	ft_putstr_fd("\n// - If you want to leave a value as default but must specify a value,\n// you can use 0 or any other number in an invalid range.\033[0m\n\n", 1);
}

int	main(int argc, char **argv)
{
	t_minirt	rt;
	int			route;

	if (argc < 2 || argc > 5)
	{
		print_usage();
		return (1);
	}
	route = parser_file_name(argv[1]);
	ft_bzero(&rt, sizeof(t_minirt));
	parse_window_size(&rt, argc, argv);
	if (scene_load(&rt.scene, argv[1], route) < 0)
	{
		scene_free(&rt.scene);
		error_manager("Invalid number of lights and/or objects. There must be at least one object and one light.");
	}
	route_msg(route, argv[1]);
	minirt_init(&rt);
	render_scene(&rt);
	mlx_loop(rt.mlx);
	minirt_cleanup(&rt);
	return (0);
}
