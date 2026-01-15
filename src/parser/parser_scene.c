/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/26 01:04:56 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

static char	*try_file_no_ppm(char *file)
{
	char	*try_rt;
	char	*try_scene;
	int		fd_tester;

	try_scene = NULL;
	try_rt = ft_strjoin(file, ".ppm");
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
		return (close(fd_tester), try_rt);
	free(try_rt);
	try_rt = ft_strjoin("scenes/textures/", file);
	try_scene = ft_strjoin(try_rt, ".ppm");
	fd_tester = open(try_scene, O_RDONLY);
	if (fd_tester >= 0)
		return (free(try_rt), close(fd_tester), try_scene);
	free(try_rt);
	free(try_scene);
	error_manager("Invalid texture. Please check if it exists.", false);
	return (0);
}

static char	*try_file_with_ppm(char *file)
{
	char	*try_rt;
	int		fd_tester;

	fd_tester = open(file, O_RDONLY);
	if (fd_tester >= 0)
		return (close(fd_tester), ft_strdup(file));
	try_rt = ft_strjoin("scenes/textures/", file);
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
		return (close(fd_tester), try_rt);
	free(try_rt);
	error_manager("Invalid texture. Please check if it exists.", false);
	return (NULL);
}

char	*parser_texture_name(char *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 4, ".ppm", 4) != 0)
		return (try_file_no_ppm(file));
	else
		return (try_file_with_ppm(file));
}

static void	process_line(t_list **result, char *line, int line_num)
{
	char		**axu_line;
	t_line_data	*line_data;
	char		*tmp;

	if (ft_strchr(line, '\n'))
	{
		tmp = line;
		line = ft_substr(line, 0, ft_strlen(line) - 1);
		free(tmp);
	}
	if (str_empty(line) == true)
	{
		free(line);
		return ;
	}
	axu_line = ft_split(line, ' ');
	free(line);
	line_data = ft_calloc(1, sizeof(t_line_data));
	line_data->line_number = line_num;
	line_data->content = axu_line;
	ft_lstadd_back(result, ft_lstnew(line_data));
}

t_primitive_escene	*escene_primiteve_constructor(char *file, int *msg)
{
	t_primitive_escene	*result;
	char				*final_file;
	t_list				**content;
	int					fd;
	char				*line;

	final_file = parser_file_name(file);
	if (!final_file)
		return (*msg = 0, NULL);
	content = ft_calloc(1, sizeof(t_list *));
	fd = open(final_file, O_RDONLY);
	if (fd < 0)
		return (free(content), free(final_file), *msg = 1, NULL);
	*msg = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(content, line, ++(*msg));
		line = get_next_line(fd);
	}
	close(fd);
	result = ft_calloc(1, sizeof(t_primitive_escene));
	if (primitive_escene_t_asignation(content, result) == -1)
		return (free(final_file), free(result), *msg = 1, NULL);
	return (free(final_file), result);
}
