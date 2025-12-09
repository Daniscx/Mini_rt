/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:54:21 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/09 22:06:58 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

void	parser_file_name(char *file)
{
	int	fd_tester;

	if (ft_strncmp(file + ft_sstrlen(file) - 2, ".rt", 2) != 0)
		error_manager("file extension isn't .rt please correct");
	fd_tester = open(file, O_RDONLY);
	if (fd_tester < 0)
		error_manager("invalid file please check if it exits");
}

bool	if_betwen_values(float element_to_check, float minmun_value,
		float maximun_value)
{
	if (element_to_check > maximun_value || element_to_check < minmun_value)
		return (false);
	return (true);
}

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
	*actual_float = ft_float(actual_element[1]);
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
				free(list_to_add_element);
				return ;
			}
			i++;
		}
		actual_float = ft_calloc(1, sizeof(float));
		*actual_float = ft_float(rgb_to_split[j]);
		if (if_betwen_values(*actual_float, 0, 250) == false)
			ft_printf("%s\n", "no valid parametter find in ambient light rgb");
		ft_lstadd_back(rgb_list, ft_lstnew(actual_float));
		j++;
	}
	ft_lstadd_back(list_to_add_element, ft_lstnew(rgb_list));
}

void	light_parser(void *actual_elem, void *list_to_add)
{
	(void)actual_elem;
	(void)list_to_add;
}

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
				free(list_to_add_element);
				return ;
			}
			i++;
		}
		actual_float = ft_calloc(1, sizeof(float));
		*actual_float = ft_float(x_y_z_to_split[j]);
		ft_lstadd_back(xyz_list, ft_lstnew(actual_float));
		j++;
	}
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
				free(list_to_add_element);
				return ;
			}
			i++;
		}
		actual_float = ft_calloc(1, sizeof(float));
		*actual_float = ft_float(x_y_z_to_split[j]);
		if (if_betwen_values(*actual_float, -1, 1) == false)
			ft_printf("%s\n", "no valid parametter find in camera vector");
		ft_lstadd_back(xyz_list, ft_lstnew(actual_float));
		j++;
	}
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
	*actual_float = ft_float(actual_element[3]);
	if (if_betwen_values(*actual_float, 0, 180) == false)
		ft_printf("%s\n", "no valid parametter find in camera vector");
	ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
}

static int	primitive_parse_t_asignation(t_list **element_to_conver,
		parse_primitive_t *struct_to_assignate)
{
	struct_to_assignate->al = general_parser(element_to_conver,
			ambient_light_parser);
	if (!struct_to_assignate->al)
		return (-1);
	struct_to_assignate->camera = general_parser(element_to_conver,
			camera_parser);
	if (!struct_to_assignate->camera)
		return (-1);
	return (0);
}

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

parse_primitive_t	*parse_primiteve_contructor(char *file)
{
	parse_primitive_t	*temp;

	parser_file_name(file);
	temp = ft_calloc(1, sizeof(parse_primitive_t));
	if (!temp)
		return (NULL);
	if (primitive_parse_t_asignation(get_file_content(file), temp) < 0)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (NULL);
}
