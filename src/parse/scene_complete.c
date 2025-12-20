/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_complete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 01:59:11 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 02:07:46 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	print_directory_message(char *file)
{
	ft_putstr_fd("\033[32mAdded directory ./scenes/ to file: \033[1;32m", 0);
	ft_putstr_fd(file, 0);
	ft_putstr_fd("\033[0m\n", 0);
}

static void	print_directory_rt_message(char *file)
{
	ft_putstr_fd("\033[32mAdded directory ./scenes/ and .rt extension: ", 0);
	ft_putstr_fd("\033[1;32m", 0);
	ft_putstr_fd(file, 0);
	ft_putstr_fd("\033[0m\n", 0);
}

static void	print_extension_message(char *file)
{
	ft_putstr_fd("\033[32mAdded .rt extension to file: \033[1;32m", 0);
	ft_putstr_fd(file, 0);
	ft_putstr_fd("\033[0m\n", 0);
}

void route_msg(int route, char *file)
{
	if(route == 1)
		print_extension_message(file);
	else if (route == 2)
		print_directory_rt_message(file);
	else if (route == 4)
		print_directory_message(file);
}
