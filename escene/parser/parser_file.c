/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/27 18:55:08 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "stdbool.h"
#include "../../includes/mini_rt.h"

/**
 * Tries to open a .rt file without .rt extension
 * First tries: filename + ".rt"
 * Then tries: "scenes/" + filename + ".rt"
 * @param file Filename without extension
 * @return Path to valid file, or NULL if not found (prints error)
 */
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
		return (try_scene);
	}
	free(try_rt);
	free(try_scene);
	error_manager("Invalid file, please check if it exists!", false);
	return (0);
}

/**
 * Tries to open a .rt file with .rt extension
 * First tries: file as given
 * Then tries: "scenes/" + file
 * @param file Filename with .rt extension
 * @return Duplicate of valid path, or NULL if not found (prints error)
 */
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
		return (try_rt);
	}
	free(try_rt);
	close(fd_tester);
	error_manager("Invalid file, please check if it exists!", false);
	return (NULL);
}

/**
 * Resolves filename and finds the actual file path
 * Handles filenames with or without .rt extension
 * Searches in current directory and scenes/ directory
 * @param file Filename to resolve
 * @return Full path to valid .rt file, or NULL on error (prints error message)
 */
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
	error_manager("Invalid texture, please check if it exists!", false);
	return (0);
}

/**
 * Tries to open a .rt file with .rt extension
 * First tries: file as given
 * Then tries: "scenes/" + file
 * @param file Filename with .rt extension
 * @return Duplicate of valid path, or NULL if not found (prints error)
 */
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
	close(fd_tester);
	error_manager("Invalid texture, please check if it exists!", false);
	return (NULL);
}

/**
 * Resolves filename and finds the actual file path
 * Handles filenames with or without .rt extension
 * Searches in current directory and scenes/ directory
 * @param file Filename to resolve
 * @return Full path to valid .rt file, or NULL on error (prints error message)
 */
char 	*parser_texture_name(char *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 4, ".ppm", 4) != 0)
		return (try_file_no_ppm(file));
	else
		return (try_file_with_ppm(file));
}


/**
 * Reads a .rt file and splits each line into separate elements
 * Skips empty lines and lines containing only whitespace
 * Each line is split by spaces into a char** array
 * All arrays are stored in a linked list
 * @param file Path to .rt file to read
 * @return Pointer to linked list of char** arrays (one per non-empty line)
 */
static t_list **get_file_content(char *file)
{
    int fd;
    t_list **result;
    char *line_to_do_split;
    char **axu_line;
	char *free_aux;
    
    result = ft_calloc(1, sizeof(t_list *));
    if(!result)
        return(NULL);
    fd = open(file, O_RDONLY);
    if(fd < 0)
        return(NULL);
    line_to_do_split = get_next_line(fd);
    while(line_to_do_split != NULL)
    {
        if(ft_strchr(line_to_do_split, '\n'))
		{
			 free_aux = ft_substr(line_to_do_split, 0, ft_strlen(line_to_do_split) - 1);
			 free(line_to_do_split);
			 line_to_do_split = free_aux;	
		}
           
        if(str_empty(line_to_do_split) == true)
            {
                free(line_to_do_split);
                line_to_do_split = get_next_line(fd);
                continue;
            }
        axu_line = ft_split(line_to_do_split, ' ');
        free(line_to_do_split);
        ft_lstadd_back(result, ft_lstnew(axu_line));
        line_to_do_split = get_next_line(fd);
    }
    close(fd);
    return(result);
}

/**
 * Main entry point for parsing a scene file
 * Reads and parses all elements from a .rt file
 * Returns a primitive scene structure with unprocessed parsed data
 * @param file Filename (with or without .rt extension)
 * @return Populated t_primitive_escene structure, or NULL on parse error
 */
t_primitive_escene *escene_primiteve_contructor(char *file)
{
    t_primitive_escene *result;
    char *final_file;
    
   final_file = parser_file_name(file);
    result = ft_calloc(1, sizeof(t_primitive_escene));
    if(primitive_escene_t_asignation(get_file_content(final_file), result) == -1)
        return(NULL);
    //print_primitive_escene(result);
    return(result);    
}
