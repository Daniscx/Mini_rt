/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:07:55 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	process_line_objects(t_scene *scene, char **args)
{
	if (ft_strncmp(args[0], "spt", 4) == 0)
		load_sphere_textured(scene, args);
	else if (ft_strncmp(args[0], "sp", 3) == 0)
		load_sphere(scene, args);
	else if (ft_strncmp(args[0], "plc", 4) == 0)
		load_plane_ex(scene, args, 1);
	else if (ft_strncmp(args[0], "pl", 3) == 0)
		load_plane(scene, args);
	else if (ft_strncmp(args[0], "cy", 3) == 0)
		load_cylinder(scene, args);
	else if (ft_strncmp(args[0], "co", 3) == 0)
		load_cone(scene, args);
}

static void	process_line(t_scene *scene, char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	if (!args || !args[0])
	{
		free_double_pointer(args);
		return ;
	}
	if (ft_strncmp(args[0], "A", 2) == 0)
		load_ambient(scene, args);
	else if (ft_strncmp(args[0], "C", 2) == 0)
		load_camera(scene, args);
	else if (ft_strncmp(args[0], "L", 2) == 0)
		load_light(scene, args);
	else
		process_line_objects(scene, args);
	free_double_pointer(args);
}

static char	*get_file_path(char *filename, int route, char **in_open)
{
	char	*to_open;

	*in_open = NULL;
	if (route == 1)
		to_open = ft_strjoin(filename, ".rt");
	else if (route == 2)
	{
		*in_open = ft_strjoin(filename, ".rt");
		to_open = ft_strjoin("scenes/", *in_open);
	}
	else if (route == 3)
		to_open = ft_strdup(filename);
	else
		to_open = ft_strjoin("scenes/", filename);
	return (to_open);
}

static void	read_scene_file(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		process_line(scene, line);
		free(line);
		line = get_next_line(fd);
	}
}

int	scene_load(t_scene *scene, char *filename, int route)
{
	int		fd;
	char	*to_open;
	char	*in_open;

	ft_bzero(scene, sizeof(t_scene));
	to_open = get_file_path(filename, route, &in_open);
	fd = open(to_open, O_RDONLY);
	if (fd < 0)
	{
		if (route == 2)
			free(in_open);
		free(to_open);
		error_manager("Failed to load scene file.");
	}
	read_scene_file(scene, fd);
	close(fd);
	if (route == 2)
		free(in_open);
	free(to_open);
	if (scene->light_count == 0 || scene->object_count == 0)
		return (-1);
	return (0);
}
