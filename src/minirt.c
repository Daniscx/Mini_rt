/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:49:37 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:46:17 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/messages.h"

void	error_manager(char *error_message, bool exit_code)
{
	if (!error_message && exit_code == true)
		exit(1);
	ft_putstr_fd("\033[1;36mminiRT: \033[1;31mError: \033[0m", STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
	if (exit_code == true)
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
	t_minirt	*rt;
	int			msg;

	if (argc < 2 || argc > 5)
	{
		ft_putstr_fd(PRINT_USAGE, STDERR_FILENO);
		return (1);
	}
	msg = 0;
	rt = ft_calloc(1, sizeof(t_minirt));
	rt->scene = escene_constructor(argv[1], &msg);
	if (rt->scene == NULL)
	{
		free(rt);
		if (msg == 1)
			error_manager("Scene construction failed.", true);
		else
			exit(1);
	}
	parse_window_size(rt, argc, argv);
	minirt_init(rt);
	render_scene(rt);
	mlx_loop(rt->mlx);
	return (0);
}
