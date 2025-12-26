/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/26 01:04:56 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/parser_internal.h"
# include "../../includes/minirt.h"

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
		ft_putstr_fd("\033[32mAdded directory ./scenes/ and .rt extension: ", 1);
		ft_putstr_fd("\033[1;32m", 1);
		ft_putstr_fd(file, 1);
		ft_putstr_fd("\033[0m\n", 1);
	}
	else if (type == 4)
	{
		ft_putstr_fd("\033[32mAdded directory ./scenes/ to file: \033[1;32m", 1);
		ft_putstr_fd(file, 1);
		ft_putstr_fd("\033[0m\n", 1);
	}
}

static char 	*try_file_no_rt(char *file)
{
	char	*try_rt;
	char	*try_scene;
	int		fd_tester;

	try_scene = NULL;
	try_rt = ft_strjoin(file, ".rt");
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
	{
		close(fd_tester);
		print_autocomplete_msg(1, file);
		return (try_rt);
	}
	free(try_rt);
	try_rt = ft_strjoin("scenes/", file);
	try_scene = ft_strjoin(try_rt, ".rt");
	fd_tester = open(try_scene, O_RDONLY);
	if (fd_tester >= 0)
	{
		free(try_rt);
		close(fd_tester);
		print_autocomplete_msg(2, file);
		return (try_scene);
	}
	free(try_rt);
	free(try_scene);
	error_manager("Invalid file. Check if it exists and/or if its extension is correct.", false);
	return (NULL);
}

static char 	*try_file_with_rt(char *file)
{
	char	*try_rt;
	int		fd_tester;

	fd_tester = open(file, O_RDONLY);
	if (fd_tester >= 0)
	{
		close(fd_tester);
		return(ft_strdup(file));
	}
	try_rt = ft_strjoin("scenes/", file);
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
	{
		close(fd_tester);
		print_autocomplete_msg(4, file);
		return (try_rt);
	}
	free(try_rt);
	error_manager("Invalid file. Check if it exists and/or if its extension is correct.", false);
	return (NULL);
}

char 	*parser_file_name(char *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 3, ".rt", 3) != 0)
		return (try_file_no_rt(file));
	else
		return (try_file_with_rt(file));
}
static char 	*try_file_no_ppm(char *file)
{
	char	*try_rt;
	char	*try_scene;
	int		fd_tester;

	try_scene = NULL;
	try_rt = ft_strjoin(file, ".ppm");
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
	{
		close(fd_tester);
		return (try_rt);
	}
	free(try_rt);
	try_rt = ft_strjoin("scenes/textures/", file);
	try_scene = ft_strjoin(try_rt, ".ppm");
	fd_tester = open(try_scene, O_RDONLY);
	if (fd_tester >= 0)
	{
		free(try_rt);
		close(fd_tester);
		return (try_scene);
	}
	free(try_rt);
	free(try_scene);
	error_manager("Invalid texture. Please check if it exists.", false);
	return (0);
}

static char 	*try_file_with_ppm(char *file)
{
	char	*try_rt;
	int		fd_tester;

	fd_tester = open(file, O_RDONLY);
	if (fd_tester >= 0)
	{
		close(fd_tester);
		return(ft_strdup(file));
	}
	try_rt = ft_strjoin("scenes/textures/", file);
	fd_tester = open(try_rt, O_RDONLY);
	if (fd_tester >= 0)
	{
		close(fd_tester);
		return (try_rt);
	}
	free(try_rt);
	error_manager("Invalid texture. Please check if it exists.", false);
	return (NULL);
}

char 	*parser_texture_name(char *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 4, ".ppm", 4) != 0)
		return (try_file_no_ppm(file));
	else
		return (try_file_with_ppm(file));
}

static t_list **get_file_content(char *file)
{
    int fd;
    t_list **result;
    char *line_to_do_split;
    char **axu_line;
    t_line_data *line_data;
    int line_number;

    result = ft_calloc(1, sizeof(t_list *));
    if(!result)
        return(NULL);
    fd = open(file, O_RDONLY);
    if(fd < 0)
    {
        free(result);
        return(NULL);
    }
    line_number = 0;
    line_to_do_split = get_next_line(fd);
    while(line_to_do_split != NULL)
    {
        line_number++;
        if(ft_strchr(line_to_do_split, '\n'))
        {
            char *tmp = line_to_do_split;
            line_to_do_split = ft_substr(line_to_do_split, 0, ft_strlen(line_to_do_split) - 1);
            free(tmp);
        }
        if(str_empty(line_to_do_split) == true)
        {
            free(line_to_do_split);
            line_to_do_split = get_next_line(fd);
            continue;
        }
        axu_line = ft_split(line_to_do_split, ' ');
        free(line_to_do_split);
        line_data = ft_calloc(1, sizeof(t_line_data));
        line_data->line_number = line_number;
        line_data->content = axu_line;
        ft_lstadd_back(result, ft_lstnew(line_data));
        line_to_do_split = get_next_line(fd);
    }
    close(fd);
    return(result);
}

t_primitive_escene *escene_primiteve_constructor(char *file, int *msg)
{
    t_primitive_escene	*result;
    char				*final_file;
    
    final_file = parser_file_name(file);
    if (!final_file)
        return (*msg = 0, NULL);
    result = ft_calloc(1, sizeof(t_primitive_escene));
    if(primitive_escene_t_asignation(get_file_content(final_file), result) == -1)
    {
        free(final_file);
        free(result);
        return(*msg = 1, NULL);
    }
    free(final_file);
    return(result);
}
