/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:54:21 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/17 22:04:53 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Prints message when directory prefix is added to filename.
*/
static void	print_directory_message(char *file)
{
	ft_putstr_fd("\033[32mAdded directory “./scenes/” to the file: \033[1;32m", 0);
	ft_putstr_fd(file, 0);
	ft_putstr_fd("\033[0m\n", 0);
}

/*
** Prints message when both directory and .rt extension are added.
*/
static void	print_directory_rt_message(char *file)
{
	ft_putstr_fd("\033[32mAdded directory “./scenes/” to the file as well as extension “.rt”: \033[1;32m", 0);
	ft_putstr_fd(file, 0);
	ft_putstr_fd("\033[0m\n", 0);
}

/*
** Prints message when .rt extension is added to filename.
*/
static void	print_extnsion_message(char *file)
{
	ft_putstr_fd("\033[32mAdded “.rt” extension to the file: \033[1;32m", 0);
	ft_putstr_fd(file, 0);
	ft_putstr_fd("\033[0m\n", 0);
}

/*
** Validates and resolves the scene file path.
** Tries different combinations of path and extension. Returns route code.
*/
int	parser_file_name(char *file)
{
	int		fd_tester;
	char	*try_rt;

	if (ft_strncmp(file + ft_strlen(file) - 3, ".rt", 3) != 0)
	{
		try_rt = ft_strjoin(file, ".rt");
		fd_tester = open(try_rt, O_RDONLY);
		if (fd_tester >= 0)
			return (print_extnsion_message(file), free(try_rt), close(fd_tester), 1);
		free(try_rt);
		try_rt = ft_strjoin("scenes/", file);
		try_rt = ft_strjoin(try_rt, ".rt");
		fd_tester = open(try_rt, O_RDONLY);
		if (fd_tester >= 0)
			return (print_directory_rt_message(file), free(try_rt), close(fd_tester), 2);
		free(try_rt);
		error_manager("invalid file, please check if it exists!");
	}
	else
	{
		fd_tester = open(file, O_RDONLY);
		if (fd_tester >= 0)
			return (close(fd_tester), 3);
		try_rt = ft_strjoin("scenes/", file);
		fd_tester = open(try_rt, O_RDONLY);
		if (fd_tester >= 0)
			return (print_directory_message(file), free(try_rt), close(fd_tester), 4);
		free(try_rt);
		close(fd_tester);
		error_manager("invalid file, please check if it exits!");
	}
	return (0);
}

/*
** Checks if a value is within a given range [min, max].
*/
bool	if_betwen_values(float element_to_check, float minmun_value, float maximun_value)
{
	if (element_to_check > maximun_value || element_to_check < minmun_value)
		return (false);
	return (true);
}

/*
** Parses an array of strings into a list of floats.
** Validates format and optionally checks value range.
*/
static t_list	**list_of_float_checker(char **splited_element, float max, float min, bool range)
{
	t_list	**result;
	int		i;
	int		j;
	float	*actual_float;

	j = 0;
	result = ft_calloc(1, sizeof(t_list *));
	while (splited_element[j])
	{
		i = 0;
		if (splited_element[j][i] == '-')
			i++;
		while (splited_element[j][i])
		{
			if (ft_isdigit(splited_element[j][i]) == 0
				&& splited_element[j][i] != '.')
			{
				ft_printf("%s\n", "invalid number format");
				return (NULL);
			}
			i++;
		}
		actual_float = ft_calloc(1, sizeof(float));
		*actual_float = ft_atof(splited_element[j]);
		if (range && if_betwen_values(*actual_float, min, max) == false)
		{
			ft_printf("%s\n", "value out of range");
			return (NULL);
		}
		ft_lstadd_back(result, ft_lstnew(actual_float));
		j++;
	}
	return (result);
}

/*
** Parses ambient light line from .rt file.
** Format: A <ratio> <r,g,b>. Validates ratio [0,1] and RGB [0,255].
*/
void	ambient_light_parser(void *actual_elem, void *list_to_add)
{
	char	**actual_element;
	t_list	**list_to_add_element;
	int		i;
	int		j;
	char	**rgb_to_split;
	t_list	**rgb_list;
	float	*actual_float;

	actual_element = (char **)actual_elem;
	list_to_add_element = (t_list **)list_to_add;
	i = 1;
	j = 0;
	if (ft_strncmp(actual_element[0], "A", ft_strlen(actual_element[0])) == 0
		&& *list_to_add_element)
		ft_printf("%s\n", "multiple ambient light declaration detected please check");
	else if (ft_strncmp(actual_element[0], "A",
			ft_strlen(actual_element[0])) != 0)
		return ;
	rgb_list = ft_calloc(1, sizeof(t_list *));
	while (actual_element[1][i])
	{
		if (ft_isdigit(actual_element[1][i]) == 0 && actual_element[1][i] != '.')
		{
			ft_printf("%s\n", "no valid parametter find in ambient light ratio");
			free(list_to_add_element);
			return ;
		}
		i++;
	}
	actual_float = ft_calloc(1, sizeof(float));
	*actual_float = ft_atof(actual_element[1]);
	if (if_betwen_values(*actual_float, 0, 1) == false)
		ft_printf("%s\n", "no valid parametter find in ambient light ratio");
	ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
	rgb_to_split = ft_split(actual_element[2], ',');
	while (rgb_to_split[j])
	{
		i = 0;
		while (rgb_to_split[j][i])
		{
			if (ft_isdigit(rgb_to_split[j][i]) == 0)
			{
				ft_printf("%s\n", "no valid parametter find in ambient light rgb");
				free_double_pointer(rgb_to_split);
				return ;
			}
			i++;
		}
		actual_float = ft_calloc(1, sizeof(float));
		*actual_float = ft_atof(rgb_to_split[j]);
		if (if_betwen_values(*actual_float, 0, 250) == false)
			ft_printf("%s\n", "no valid parametter find in ambient light rgb");
		ft_lstadd_back(rgb_list, ft_lstnew(actual_float));
		j++;
	}
	free_double_pointer(rgb_to_split);
	ft_lstadd_back(list_to_add_element, ft_lstnew(rgb_list));
}

/*
** Parses point light line from .rt file.
** Format: L <x,y,z> <brightness> <r,g,b>
*/
void	light_parser(void *actual_elem, void *list_to_add)
{
	char	**actual_element;
	t_list	**list_to_add_element;
	t_list	**new_light_element;
	char	**splited_element;
	int		i;
	float	*actual_float;

	actual_element = (char **)actual_elem;
	list_to_add_element = (t_list **)list_to_add;
	i = 0;
	if (ft_strncmp(actual_element[0], "L", ft_strlen(actual_element[0])) != 0)
		return ;
	new_light_element = ft_calloc(1, sizeof(t_list *));
	splited_element = ft_split(actual_element[1], ',');
	if (!splited_element)
		return ;
	ft_lstadd_back(new_light_element, ft_lstnew(list_of_float_checker(splited_element, 0, 0, false)));
	free_double_pointer(splited_element);
	while (actual_element[2][i])
	{
		if (ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
		{
			ft_printf("%s\n", "no valid parameter in light brightness");
			return ;
		}
		i++;
	}
	actual_float = ft_calloc(1, sizeof(float));
	*actual_float = ft_atof(actual_element[2]);
	if (if_betwen_values(*actual_float, 0, 1) == false)
		ft_printf("%s\n", "light brightness out of range [0.0, 1.0]");
	ft_lstadd_back(new_light_element, ft_lstnew(actual_float));
	splited_element = ft_split(actual_element[3], ',');
	if (!splited_element)
		return ;
	ft_lstadd_back(new_light_element, ft_lstnew(list_of_float_checker(splited_element, 255, 0, true)));
	free_double_pointer(splited_element);
	ft_lstadd_back(list_to_add_element, ft_lstnew(new_light_element));
}

/*
** Generic parser that iterates a list and applies a parser function.
** Each parser function decides whether to process or skip each line.
*/
t_list	**general_parser(t_list **list__to_track, void (*f)(void *, void *))
{
	t_list	**result;
	t_list	*actual_node;

	if (!list__to_track || *list__to_track == NULL)
		return (NULL);
	result = ft_calloc(1, sizeof(t_list *));
	actual_node = *list__to_track;
	while (actual_node)
	{
		f(actual_node->content, result);
		if (!result)
			return (NULL);
		actual_node = actual_node->next;
	}
	return (result);
}

/*
** Parses camera line from .rt file.
** Format: C <x,y,z> <nx,ny,nz> <fov>. Direction should be normalized.
*/
void	camera_parser(void *actual_elem, void *list_to_add)
{
	char	**actual_element;
	t_list	**list_to_add_element;
	int		i;
	int		j;
	char	**x_y_z_to_split;
	t_list	**xyz_list;
	float	*actual_float;

	actual_element = (char **)actual_elem;
	list_to_add_element = (t_list **)list_to_add;
	i = 0;
	j = 0;
	if (ft_strncmp(actual_element[0], "C", ft_strlen(actual_element[0])) == 0
		&& *list_to_add_element)
		ft_printf("%s\n", "multiple Camaera declaration detected please check");
	else if (ft_strncmp(actual_element[0], "C",
			ft_strlen(actual_element[0])) != 0)
		return ;
	xyz_list = ft_calloc(1, sizeof(t_list *));
	x_y_z_to_split = ft_split(actual_element[1], ',');
	while (x_y_z_to_split[j])
	{
		i = 0;
		if (x_y_z_to_split[j][i] == '-')
			i++;
		while (x_y_z_to_split[j][i])
		{
			if (ft_isdigit(x_y_z_to_split[j][i]) == 0
				&& x_y_z_to_split[j][i] != '.')
			{
				ft_printf("%s\n", "no valid parametter find in camera position rgb");
				free_double_pointer(x_y_z_to_split);
				return ;
			}
			i++;
		}
		actual_float = ft_calloc(1, sizeof(float));
		*actual_float = ft_atof(x_y_z_to_split[j]);
		ft_lstadd_back(xyz_list, ft_lstnew(actual_float));
		j++;
	}
	free_double_pointer(x_y_z_to_split);
	ft_lstadd_back(list_to_add_element, ft_lstnew(xyz_list));
	i = 0;
	j = 0;
	xyz_list = ft_calloc(1, sizeof(t_list *));
	x_y_z_to_split = ft_split(actual_element[2], ',');
	while (x_y_z_to_split[j])
	{
		i = 0;
		if (x_y_z_to_split[j][i] == '-')
			i++;
		while (x_y_z_to_split[j][i])
		{
			if (ft_isdigit(x_y_z_to_split[j][i]) == 0
				&& x_y_z_to_split[j][i] != '.')
			{
				ft_printf("%s\n", "no valid parametter find in camera vector rgb");
				free_double_pointer(x_y_z_to_split);
				return ;
			}
			i++;
		}
		actual_float = ft_calloc(1, sizeof(float));
		*actual_float = ft_atof(x_y_z_to_split[j]);
		if (if_betwen_values(*actual_float, -1, 1) == false)
			ft_printf("%s\n", "no valid parametter find in camera vector");
		ft_lstadd_back(xyz_list, ft_lstnew(actual_float));
		j++;
	}
	free_double_pointer(x_y_z_to_split);
	ft_lstadd_back(list_to_add_element, ft_lstnew(xyz_list));
	i = 0;
	while (actual_element[3][i])
	{
		if (ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
		{
			ft_printf("%s\n", "no valid parametter find in ambient light ratio");
			free(list_to_add_element);
			return ;
		}
		i++;
	}
	actual_float = ft_calloc(1, sizeof(float));
	*actual_float = ft_atof(actual_element[3]);
	if (if_betwen_values(*actual_float, 0, 180) == false)
		ft_printf("%s\n", "no valid parametter find in camera vector");
	ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
}

/*
** Parses sphere object. Format: sp <x,y,z> <diameter> <r,g,b>
*/
static t_list	**sphere_parser(char **actual_element)
{
	t_list	**result;
	t_list	**float_list;
	char	**element_splited;
	float	*actual_float;
	int		i;

	result = ft_calloc(1, sizeof(t_list *));
	ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
	element_splited = ft_split(actual_element[1], ',');
	float_list = list_of_float_checker(element_splited, 0, 0, false);
	free_double_pointer(element_splited);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	i = 0;
	if (actual_element[2][i] == '-')
		i++;
	while (actual_element[2][i])
	{
		if (ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
			return (ft_printf("%s\n", "invalid sphere diameter"), free(result), NULL);
		i++;
	}
	actual_float = ft_calloc(1, sizeof(float));
	*actual_float = ft_atof(actual_element[2]);
	ft_lstadd_back(result, ft_lstnew(actual_float));
	element_splited = ft_split(actual_element[3], ',');
	float_list = list_of_float_checker(element_splited, 255, 0, true);
	free_double_pointer(element_splited);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	return (result);
}

/*
** Parses plane object. Format: pl <x,y,z> <nx,ny,nz> <r,g,b>
*/
static t_list	**plane_parser(char **actual_element)
{
	t_list	**result;
	t_list	**float_list;
	char	**element_splited;

	result = ft_calloc(1, sizeof(t_list *));
	ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
	element_splited = ft_split(actual_element[1], ',');
	float_list = list_of_float_checker(element_splited, 0, 0, false);
	free_double_pointer(element_splited);
	if (!float_list)
		return (ft_printf("%s\n", "invalid plane position"), free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	element_splited = ft_split(actual_element[2], ',');
	float_list = list_of_float_checker(element_splited, 1, -1, true);
	free_double_pointer(element_splited);
	if (!float_list)
		return (ft_printf("%s\n", "invalid plane normal"), free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	element_splited = ft_split(actual_element[3], ',');
	float_list = list_of_float_checker(element_splited, 255, 0, true);
	free_double_pointer(element_splited);
	if (!float_list)
		return (ft_printf("%s\n", "invalid plane color"), free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	return (result);
}

/*
** Parses cylinder object. Format: cy <x,y,z> <nx,ny,nz> <diam> <height> <r,g,b>
*/
static t_list	**cylinder_parser(char **actual_element)
{
	t_list	**result;
	t_list	**float_list;
	char	**element_splited;
	float	*actual_float;
	int		i;

	result = ft_calloc(1, sizeof(t_list *));
	ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
	element_splited = ft_split(actual_element[1], ',');
	float_list = list_of_float_checker(element_splited, 0, 0, false);
	free_double_pointer(element_splited);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	element_splited = ft_split(actual_element[2], ',');
	float_list = list_of_float_checker(element_splited, 1, -1, true);
	free_double_pointer(element_splited);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	i = 0;
	if (actual_element[3][i] == '-')
		i++;
	while (actual_element[3][i])
	{
		if (ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
			return (ft_printf("%s\n", "invalid cylinder diameter"), free(result), NULL);
		i++;
	}
	actual_float = ft_calloc(1, sizeof(float));
	*actual_float = ft_atof(actual_element[3]);
	ft_lstadd_back(result, ft_lstnew(actual_float));
	i = 0;
	if (actual_element[4][i] == '-')
		i++;
	while (actual_element[4][i])
	{
		if (ft_isdigit(actual_element[4][i]) == 0 && actual_element[4][i] != '.')
			return (ft_printf("%s\n", "invalid cylinder height"), free(result), NULL);
		i++;
	}
	actual_float = ft_calloc(1, sizeof(float));
	*actual_float = ft_atof(actual_element[4]);
	ft_lstadd_back(result, ft_lstnew(actual_float));
	element_splited = ft_split(actual_element[5], ',');
	float_list = list_of_float_checker(element_splited, 255, 0, true);
	free_double_pointer(element_splited);
	if (!float_list)
		return (free(result), NULL);
	ft_lstadd_back(result, ft_lstnew(float_list));
	return (result);
}

/*
** Delegates to specific object parsers based on type identifier.
*/
static void	object_parser(void *actual_elem, void *list_to_add)
{
	char	**actual_element;
	t_list	**list_to_add_element;
	t_list	**result;
	size_t	len;

	actual_element = (char **)actual_elem;
	list_to_add_element = (t_list **)list_to_add;
	len = ft_strlen(actual_element[0]);
	if (ft_strncmp(actual_element[0], "sp", len) == 0)
	{
		result = sphere_parser(actual_element);
		if (result)
			ft_lstadd_back(list_to_add_element, ft_lstnew(result));
	}
	else if (ft_strncmp(actual_element[0], "pl", len) == 0)
	{
		result = plane_parser(actual_element);
		if (result)
			ft_lstadd_back(list_to_add_element, ft_lstnew(result));
	}
	else if (ft_strncmp(actual_element[0], "cy", len) == 0)
	{
		result = cylinder_parser(actual_element);
		if (result)
			ft_lstadd_back(list_to_add_element, ft_lstnew(result));
	}
}

/*
** Assigns parsed elements to the t_parse_prim structure.
** Parses ambient light, camera, lights and objects. Returns 0 on success.
*/
static int	primitive_parse_t_asignation(t_list **element_to_conver, t_parse_prim *struct_to_assignate)
{
	struct_to_assignate->al = general_parser(element_to_conver, ambient_light_parser);
	if (!struct_to_assignate->al)
		return (-1);
	struct_to_assignate->camera = general_parser(element_to_conver, camera_parser);
	if (!struct_to_assignate->camera)
		return (-1);
	struct_to_assignate->light = general_parser(element_to_conver, light_parser);
	struct_to_assignate->object = general_parser(element_to_conver, object_parser);
	return (0);
}

/*
** Reads .rt file content and stores each line as a split array in a list.
*/
static t_list	**get_file_content(char *file)
{
	int		fd;
	t_list	**result;
	char	*line_to_do_split;
	char	**axu_line;

	result = ft_calloc(1, sizeof(t_list *));
	if (!result)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line_to_do_split = get_next_line(fd);
	while (line_to_do_split != NULL)
	{
		axu_line = ft_split(line_to_do_split, ' ');
		free(line_to_do_split);
		ft_lstadd_back(result, ft_lstnew(axu_line));
		line_to_do_split = get_next_line(fd);
	}
	close(fd);
	return (result);
}

/*
** Recursively frees a list and its content nodes.
*/
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

/*
** Destructor for t_parse_prim. Frees all allocated memory.
*/
void	*parse_primiteve_destructor(t_parse_prim *parse)
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

/*
** Main parser constructor. Reads and parses the .rt scene file.
*/
t_parse_prim	*parse_primiteve_contructor(char *file)
{
	t_parse_prim	*temp;

	parser_file_name(file);
	temp = ft_calloc(1, sizeof(t_parse_prim));
	if (!temp)
		return (NULL);
	if (primitive_parse_t_asignation(get_file_content(file), temp) < 0)
	{
		parse_primiteve_destructor(temp);
		return (NULL);
	}
	return (temp);
}
