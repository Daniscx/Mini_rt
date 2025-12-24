/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_assignment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:30:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:17:42 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/parser_internal.h"
# include "../../includes/minirt.h"

static void	free_file_content(t_list **content)
{
	t_list		*aux;
	t_list		*tmp;
	t_line_data	*line_data;

	if (!content)
		return ;
	if (!*content)
		return (free(content));
	aux = *content;
	while (aux)
	{
		tmp = aux->next;
		if (aux->content)
		{
			line_data = (t_line_data *)aux->content;
			if (line_data->content)
				free_double_pointer(line_data->content);
			free(line_data);
		}
		free(aux);
		aux = tmp;
	}
	free(content);
}

static void	process_all_lines(t_list **element_to_conver, t_primitive_escene *s, t_error_list *errors, int *has_errors)
{
	t_list		*actual_node;
	t_line_data	*line_data;
	int			ret;

	actual_node = *element_to_conver;
	while (actual_node)
	{
		line_data = (t_line_data *)actual_node->content;
		if (correct_number_of_elements(line_data->content, line_data->line_number, errors) == false)
		{
			*has_errors = 1;
			actual_node = actual_node->next;
			continue;
		}
		ret = ambient_light_parser(line_data->content, s->al, line_data->line_number, errors);
		if (ret != 0)
		{
			if (ret == -1)
				*has_errors = 1;
			actual_node = actual_node->next;
			continue;
		}
		ret = camera_parser(line_data->content, s->camera, line_data->line_number, errors);
		if (ret != 0)
		{
			if (ret == -1)
				*has_errors = 1;
			actual_node = actual_node->next;
			continue;
		}
		ret = light_parser(line_data->content, s->light, line_data->line_number, errors);
		if (ret != 0)
		{
			if (ret == -1)
				*has_errors = 1;
			actual_node = actual_node->next;
			continue;
		}
		ret = object_parser(line_data->content, s->object, line_data->line_number, errors);
		if (ret != 0)
		{
			if (ret == -1)
				*has_errors = 1;
		}
		actual_node = actual_node->next;
	}
}

int    primitive_escene_t_asignation(t_list **element_to_conver, t_primitive_escene *s)
{
    t_error_list	*errors;
    int				has_errors;

    errors = error_list_create();
    has_errors = 0;
    s->al = ft_calloc(1, sizeof(t_list *));
    s->camera = ft_calloc(1, sizeof(t_list *));
    s->light = ft_calloc(1, sizeof(t_list *));
    s->object = ft_calloc(1, sizeof(t_list *));
    process_all_lines(element_to_conver, s, errors, &has_errors);
    if (has_errors)
    {
        error_list_print(errors);
        error_list_free(errors);
        if (s->al)
            free_al_primitive(s->al);
        if (s->camera)
            free_list_camera_primitive(s->camera);
        if (s->light)
            free_list_of_lights_primitive(s->light);
        if (s->object)
            list_of_objects_destructor_primitive(s->object);
        return (free_file_content(element_to_conver), -1);
    }
    error_list_free(errors);
    free_file_content(element_to_conver);
    return (0);
}

t_list	**get_list_of_elements(t_primitive_escene *primitive, enum e_type_list identifcator)
{
    if(identifcator == AL)
        return(primitive->al);
    else if(identifcator == L)
        return(primitive->light);
    else if(identifcator == C)
        return(primitive->camera);
    else if(identifcator == OB)
        return(primitive->object);
    return(NULL);
}
