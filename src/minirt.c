/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:07:23 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 19:15:29 by ravazque         ###   ########.fr       */
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
			printf("%s %i\n", DEF_W, WIDTH_LOW);
			rt->win_w = WIDTH_LOW;
		}
		if (rt->win_h < 240 || rt->win_h > 2160)
		{
			printf("%s %i\n", DEF_H, HEIGHT_LOW);
			rt->win_h = HEIGHT_LOW;
		}
		if (rt->frame_rate < 24 || rt->frame_rate > 60)
		{
			printf("%s %i\n", DEF_FPS, TARGET_FPS);
			rt->frame_rate = TARGET_FPS;
		}
	}
}

int	main(int argc, char **argv)
{
	t_minirt	rt;
	int			route;

	if (argc < 2 || argc > 5)
	{
		ft_putstr_fd(PRINT_USAGE, STDERR_FILENO);
		return (1);
	}
	route = parser_file_name(argv[1]);
	ft_bzero(&rt, sizeof(t_minirt));
	if (scene_load(&rt.scene, argv[1], route) < 0)
	{
		scene_free(&rt.scene);
		error_manager(INVALID_OBJECTS);
	}
	route_msg(route, argv[1]);
	parse_window_size(&rt, argc, argv);
	minirt_init(&rt);
	render_scene(&rt);
	mlx_loop(rt.mlx);
	minirt_cleanup(&rt);
	return (0);
}
