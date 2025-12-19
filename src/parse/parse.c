/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:54:21 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/19 14:24:26 by ravazque         ###   ########.fr       */
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

static int	try_file_no_rt(char *file)
{
	char	*try_rt;
	char	*try_scene;
	int		fd_tester;

	try_scene = NULL;
	try_rt = ft_strjoin(file, ".rt");
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
	{
		print_extension_message(file);
		free(try_rt);
		close(fd_tester);
		return (1);
	}
	free(try_rt);
	try_rt = ft_strjoin("scenes/", file);
	try_scene = ft_strjoin(try_rt, ".rt");
	fd_tester = open(try_scene, O_RDONLY);
	if (fd_tester >= 0)
	{
		print_directory_rt_message(file);
		free(try_rt);
		free(try_scene);
		close(fd_tester);
		return (2);
	}
	free(try_rt);
	free(try_scene);
	error_manager("Invalid file, please check if it exists!");
	return (0);
}

static int	try_file_with_rt(char *file)
{
	char	*try_rt;
	int		fd_tester;

	fd_tester = open(file, O_RDONLY);
	if (fd_tester >= 0)
	{
		close(fd_tester);
		return (3);
	}
	try_rt = ft_strjoin("scenes/", file);
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
	{
		print_directory_message(file);
		free(try_rt);
		close(fd_tester);
		return (4);
	}
	free(try_rt);
	close(fd_tester);
	error_manager("Invalid file, please check if it exists!");
	return (0);
}

int	parser_file_name(char *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 3, ".rt", 3) != 0)
		return (try_file_no_rt(file));
	else
		return (try_file_with_rt(file));
}

bool	if_between_values(float elem, float min_val, float max_val)
{
	if (elem > max_val || elem < min_val)
		return (false);
	return (true);
}

static t_list	**list_of_float_checker(char **split, float max, float min,
		bool range)
{
	t_list	**result;
	int		i;
	int		j;
	float	*f;

	j = 0;
	result = ft_calloc(1, sizeof(t_list *));
	while (split[j])
	{
		i = 0;
		if (split[j][i] == '-')
			i++;
		while (split[j][i])
		{
			if (ft_isdigit(split[j][i]) == 0 && split[j][i] != '.')
				return (ft_printf("%s\n", "Invalid number format"), NULL);
			i++;
		}
		f = ft_calloc(1, sizeof(float));
		*f = ft_atof(split[j]);
		if (range && if_between_values(*f, min, max) == false)
			return (ft_printf("%s\n", "Value out of range"), NULL);
		ft_lstadd_back(result, ft_lstnew(f));
		j++;
	}
	return (result);
}

static void	parse_ambient_rgb(char **rgb_split, t_list **rgb_list)
{
	int		i;
	int		j;
	float	*f;

	j = 0;
	while (rgb_split[j])
	{
		i = 0;
		while (rgb_split[j][i])
		{
			if (ft_isdigit(rgb_split[j][i]) == 0)
			{
				ft_printf("%s\n", "Invalid parameter in ambient light RGB");
				return ;
			}
			i++;
		}
		f = ft_calloc(1, sizeof(float));
		*f = ft_atof(rgb_split[j]);
		if (if_between_values(*f, 0, 255) == false)
			ft_printf("%s\n", "Ambient light RGB out of range [0, 255]");
		ft_lstadd_back(rgb_list, ft_lstnew(f));
		j++;
	}
}

void	ambient_light_parser(void *elem, void *list)
{
	char	**args;
	t_list	**list_add;
	int		i;
	char	**rgb_split;
	t_list	**rgb_list;
	float	*f;

	args = (char **)elem;
	list_add = (t_list **)list;
	i = 1;
	if (ft_strncmp(args[0], "A", ft_strlen(args[0])) == 0 && *list_add)
		ft_printf("%s\n", "Multiple ambient light declaration detected");
	else if (ft_strncmp(args[0], "A", ft_strlen(args[0])) != 0)
		return ;
	rgb_list = ft_calloc(1, sizeof(t_list *));
	while (args[1][i])
	{
		if (ft_isdigit(args[1][i]) == 0 && args[1][i] != '.')
			return (ft_printf("%s\n", "Invalid ambient light ratio"), (void)0);
		i++;
	}
	f = ft_calloc(1, sizeof(float));
	*f = ft_atof(args[1]);
	if (if_between_values(*f, 0, 1) == false)
		ft_printf("%s\n", "Ambient light ratio out of range [0.0, 1.0]");
	ft_lstadd_back(list_add, ft_lstnew(f));
	rgb_split = ft_split(args[2], ',');
	parse_ambient_rgb(rgb_split, rgb_list);
	free_double_pointer(rgb_split);
	ft_lstadd_back(list_add, ft_lstnew(rgb_list));
}

static void	light_parser_brightness(char **args, t_list **new_light, int i)
{
	float	*f;

	while (args[2][i])
	{
		if (ft_isdigit(args[2][i]) == 0 && args[2][i] != '.')
		{
			ft_printf("%s\n", "Invalid parameter in light brightness");
			return ;
		}
		i++;
	}
	f = ft_calloc(1, sizeof(float));
	*f = ft_atof(args[2]);
	if (if_between_values(*f, 0, 1) == false)
		ft_printf("%s\n", "Light brightness out of range [0.0, 1.0]");
	ft_lstadd_back(new_light, ft_lstnew(f));
}

void	light_parser(void *elem, void *list)
{
	char	**args;
	t_list	**list_add;
	t_list	**new_light;
	char	**split;

	args = (char **)elem;
	list_add = (t_list **)list;
	if (ft_strncmp(args[0], "L", ft_strlen(args[0])) != 0)
		return ;
	new_light = ft_calloc(1, sizeof(t_list *));
	split = ft_split(args[1], ',');
	if (!split)
		return ;
	ft_lstadd_back(new_light, ft_lstnew(list_of_float_checker(split, 0, 0, 0)));
	free_double_pointer(split);
	light_parser_brightness(args, new_light, 0);
	split = ft_split(args[3], ',');
	if (!split)
		return ;
	ft_lstadd_back(new_light, ft_lstnew(list_of_float_checker(split, 255, 0, 1)));
	free_double_pointer(split);
	ft_lstadd_back(list_add, ft_lstnew(new_light));
}

t_list	**general_parser(t_list **list_track, void (*f)(void *, void *))
{
	t_list	**result;
	t_list	*node;

	if (!list_track || *list_track == NULL)
		return (NULL);
	result = ft_calloc(1, sizeof(t_list *));
	node = *list_track;
	while (node)
	{
		f(node->content, result);
		if (!result)
			return (NULL);
		node = node->next;
	}
	return (result);
}

static void	camera_parse_position(char **xyz_split, t_list **xyz_list)
{
	int		i;
	int		j;
	float	*f;

	j = 0;
	while (xyz_split[j])
	{
		i = 0;
		if (xyz_split[j][i] == '-')
			i++;
		while (xyz_split[j][i])
		{
			if (ft_isdigit(xyz_split[j][i]) == 0 && xyz_split[j][i] != '.')
			{
				ft_printf("%s\n", "Invalid parameter in camera position");
				free_double_pointer(xyz_split);
				return ;
			}
			i++;
		}
		f = ft_calloc(1, sizeof(float));
		*f = ft_atof(xyz_split[j]);
		ft_lstadd_back(xyz_list, ft_lstnew(f));
		j++;
	}
}

static void	camera_parse_direction(char **xyz_split, t_list **list_add)
{
	int		i;
	int		j;
	float	*f;
	t_list	**xyz_list;

	j = 0;
	xyz_list = ft_calloc(1, sizeof(t_list *));
	while (xyz_split[j])
	{
		i = 0;
		if (xyz_split[j][i] == '-')
			i++;
		while (xyz_split[j][i])
		{
			if (ft_isdigit(xyz_split[j][i]) == 0 && xyz_split[j][i] != '.')
				return (ft_printf("%s\n", "Invalid camera direction"), (void)0);
			i++;
		}
		f = ft_calloc(1, sizeof(float));
		*f = ft_atof(xyz_split[j]);
		if (if_between_values(*f, -1, 1) == false)
			ft_printf("%s\n", "Camera direction out of range [-1, 1]");
		ft_lstadd_back(xyz_list, ft_lstnew(f));
		j++;
	}
	ft_lstadd_back(list_add, ft_lstnew(xyz_list));
}

static void	camera_parse_fov(char **args, t_list **list_add)
{
	int		i;
	float	*f;

	i = 0;
	while (args[3][i])
	{
		if (ft_isdigit(args[3][i]) == 0 && args[3][i] != '.')
		{
			ft_printf("%s\n", "Invalid camera FOV");
			return ;
		}
		i++;
	}
	f = ft_calloc(1, sizeof(float));
	*f = ft_atof(args[3]);
	if (if_between_values(*f, 0, 180) == false)
		ft_printf("%s\n", "Camera FOV out of range [0, 180]");
	ft_lstadd_back(list_add, ft_lstnew(f));
}

void	camera_parser(void *elem, void *list)
{
	char	**args;
	t_list	**list_add;
	char	**xyz_split;
	t_list	**xyz_list;

	args = (char **)elem;
	list_add = (t_list **)list;
	if (ft_strncmp(args[0], "C", ft_strlen(args[0])) == 0 && *list_add)
		ft_printf("%s\n", "Multiple camera declaration detected");
	else if (ft_strncmp(args[0], "C", ft_strlen(args[0])) != 0)
		return ;
	xyz_list = ft_calloc(1, sizeof(t_list *));
	xyz_split = ft_split(args[1], ',');
	camera_parse_position(xyz_split, xyz_list);
	free_double_pointer(xyz_split);
	ft_lstadd_back(list_add, ft_lstnew(xyz_list));
	xyz_split = ft_split(args[2], ',');
	camera_parse_direction(xyz_split, list_add);
	free_double_pointer(xyz_split);
	camera_parse_fov(args, list_add);
}

static t_list	**sphere_parser(char **args)
{
	t_list	**result;
	t_list	**float_list;
	char	**split;
	float	*f;
	int		i;

	result = ft_calloc(1, sizeof(t_list *));
	ft_lstadd_back(result, ft_lstnew(ft_strdup(args[0])));
	split = ft_split(args[1], ',');
	float_list = list_of_float_checker(split, 0, 0, false);
	free_double_pointer(split);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	i = 0;
	if (args[2][i] == '-')
		i++;
	while (args[2][i])
	{
		if (ft_isdigit(args[2][i]) == 0 && args[2][i] != '.')
			return (ft_printf("%s\n", "Invalid sphere diameter"), NULL);
		i++;
	}
	f = ft_calloc(1, sizeof(float));
	*f = ft_atof(args[2]);
	ft_lstadd_back(result, ft_lstnew(f));
	split = ft_split(args[3], ',');
	float_list = list_of_float_checker(split, 255, 0, true);
	free_double_pointer(split);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	return (result);
}

static t_list	**plane_parser(char **args)
{
	t_list	**result;
	t_list	**float_list;
	char	**split;

	result = ft_calloc(1, sizeof(t_list *));
	ft_lstadd_back(result, ft_lstnew(ft_strdup(args[0])));
	split = ft_split(args[1], ',');
	float_list = list_of_float_checker(split, 0, 0, false);
	free_double_pointer(split);
	if (!float_list)
		return (ft_printf("%s\n", "Invalid plane position"), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	split = ft_split(args[2], ',');
	float_list = list_of_float_checker(split, 1, -1, true);
	free_double_pointer(split);
	if (!float_list)
		return (ft_printf("%s\n", "Invalid plane normal"), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	split = ft_split(args[3], ',');
	float_list = list_of_float_checker(split, 255, 0, true);
	free_double_pointer(split);
	if (!float_list)
		return (ft_printf("%s\n", "Invalid plane color"), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	return (result);
}

static t_list	**cylinder_parser_color(char **args, t_list **result)
{
	t_list	**float_list;
	char	**split;

	split = ft_split(args[5], ',');
	float_list = list_of_float_checker(split, 255, 0, true);
	free_double_pointer(split);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	return (result);
}

static t_list	**cylinder_parser(char **args)
{
	t_list	**result;
	t_list	**float_list;
	char	**split;
	float	*f;
	int		i;

	result = ft_calloc(1, sizeof(t_list *));
	ft_lstadd_back(result, ft_lstnew(ft_strdup(args[0])));
	split = ft_split(args[1], ',');
	float_list = list_of_float_checker(split, 0, 0, false);
	free_double_pointer(split);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	split = ft_split(args[2], ',');
	float_list = list_of_float_checker(split, 1, -1, true);
	free_double_pointer(split);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	i = -1;
	if (args[3][0] == '-')
		i++;
	while (args[3][++i])
		if (ft_isdigit(args[3][i]) == 0 && args[3][i] != '.')
			return (ft_printf("%s\n", "Invalid cylinder diameter"), NULL);
	f = ft_calloc(1, sizeof(float));
	*f = ft_atof(args[3]);
	ft_lstadd_back(result, ft_lstnew(f));
	i = -1;
	if (args[4][0] == '-')
		i++;
	while (args[4][++i])
		if (ft_isdigit(args[4][i]) == 0 && args[4][i] != '.')
			return (ft_printf("%s\n", "Invalid cylinder height"), NULL);
	f = ft_calloc(1, sizeof(float));
	*f = ft_atof(args[4]);
	ft_lstadd_back(result, ft_lstnew(f));
	return (cylinder_parser_color(args, result));
}

static void	object_parser(void *elem, void *list)
{
	char	**args;
	t_list	**list_add;
	t_list	**result;
	size_t	len;

	args = (char **)elem;
	list_add = (t_list **)list;
	len = ft_strlen(args[0]);
	if (ft_strncmp(args[0], "sp", len) == 0)
	{
		result = sphere_parser(args);
		if (result)
			ft_lstadd_back(list_add, ft_lstnew(result));
	}
	else if (ft_strncmp(args[0], "pl", len) == 0)
	{
		result = plane_parser(args);
		if (result)
			ft_lstadd_back(list_add, ft_lstnew(result));
	}
	else if (ft_strncmp(args[0], "cy", len) == 0)
	{
		result = cylinder_parser(args);
		if (result)
			ft_lstadd_back(list_add, ft_lstnew(result));
	}
}

static int	primitive_parse_assign(t_list **elem, t_parse_prim *prim)
{
	prim->al = general_parser(elem, ambient_light_parser);
	if (!prim->al)
		return (-1);
	prim->camera = general_parser(elem, camera_parser);
	if (!prim->camera)
		return (-1);
	prim->light = general_parser(elem, light_parser);
	prim->object = general_parser(elem, object_parser);
	return (0);
}

static t_list	**get_file_content(char *file)
{
	int		fd;
	t_list	**result;
	char	*line;
	char	**split;

	result = ft_calloc(1, sizeof(t_list *));
	if (!result)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		split = ft_split(line, ' ');
		free(line);
		ft_lstadd_back(result, ft_lstnew(split));
		line = get_next_line(fd);
	}
	close(fd);
	return (result);
}

static void	free_list_recursive(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list->next;
		if (list->content)
			free(list->content);
		free(list);
		list = temp;
	}
}

void	*parse_primitive_destructor(t_parse_prim *parse)
{
	if (!parse)
		return (NULL);
	if (parse->al && *parse->al)
		free_list_recursive(*parse->al);
	if (parse->al)
		free(parse->al);
	if (parse->camera && *parse->camera)
		free_list_recursive(*parse->camera);
	if (parse->camera)
		free(parse->camera);
	if (parse->light && *parse->light)
		free_list_recursive(*parse->light);
	if (parse->light)
		free(parse->light);
	if (parse->object && *parse->object)
		free_list_recursive(*parse->object);
	if (parse->object)
		free(parse->object);
	free(parse);
	return (NULL);
}

t_parse_prim	*parse_primitive_constructor(char *file)
{
	t_parse_prim	*temp;

	parser_file_name(file);
	temp = ft_calloc(1, sizeof(t_parse_prim));
	if (!temp)
		return (NULL);
	if (primitive_parse_assign(get_file_content(file), temp) < 0)
	{
		parse_primitive_destructor(temp);
		return (NULL);
	}
	return (temp);
}
