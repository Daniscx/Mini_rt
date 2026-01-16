/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2026/01/16 21:15:20 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

static void	print_autocomplete_msg(int type, char *file)
{
	if (type == 1)
	{
		ft_putstr_fd("\033[32mAdded .rt extension to file: \033[1;32m", 1);
		ft_putstr_fd(file, 1);
		ft_putstr_fd("\033[0m\n", 1);
	}
	else if (type == 2)
	{
		ft_putstr_fd("\033[32mAdded dir ./scenes/ and .rt ext: \033[1;32m", 1);
		ft_putstr_fd(file, 1);
		ft_putstr_fd("\033[0m\n", 1);
	}
	else if (type == 4)
	{
		ft_putstr_fd("\033[32mAdded dir ./scenes/ to file: \033[1;32m", 1);
		ft_putstr_fd(file, 1);
		ft_putstr_fd("\033[0m\n", 1);
	}
}

static char	*try_file_no_rt(char *file)
{
	char	*try_rt;
	char	*try_scene;
	int		fd_tester;

	try_scene = NULL;
	try_rt = ft_strjoin(file, ".rt");
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
		return (close(fd_tester), print_autocomplete_msg(1, file), try_rt);
	free(try_rt);
	try_rt = ft_strjoin("scenes/", file);
	try_scene = ft_strjoin(try_rt, ".rt");
	fd_tester = open(try_scene, O_RDONLY);
	if (fd_tester >= 0)
	{
		free(try_rt);
		return (close(fd_tester), print_autocomplete_msg(2, file), try_scene);
	}
	free(try_rt);
	free(try_scene);
	error_manager("Invalid file. Check the extension if the file exists.", false);
	return (NULL);
}

static char	*try_file_with_rt(char *file)
{
	char	*try_rt;
	int		fd_tester;

	fd_tester = open(file, O_RDONLY);
	if (fd_tester >= 0)
		return (close(fd_tester), ft_strdup(file));
	try_rt = ft_strjoin("scenes/", file);
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
	{
		close(fd_tester);
		print_autocomplete_msg(4, file);
		return (try_rt);
	}
	free(try_rt);
	error_manager("Invalid file. Check the extension if the file exists.", false);
	return (NULL);
}

char	*parser_file_name(char *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 3, ".rt", 3) != 0)
		return (try_file_no_rt(file));
	else
		return (try_file_with_rt(file));
}
