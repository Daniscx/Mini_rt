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

/*
** Valida que el archivo de entrada tenga extensión .rt y que exista.
** Parámetros:
**   - file: ruta al archivo de escena a validar
** Comportamiento:
**   - Verifica que termine en ".rt"
**   - Intenta abrir el archivo para comprobar que existe
**   - Llama a error_manager si hay algún problema
** NOTA: No cierra el file descriptor después de abrirlo (fuga menor)
*/
void	parser_file_name(char *file)
{
	int	fd_tester;

	if (ft_strncmp(file + ft_strlen(file) - 3, ".rt", 3) != 0)
		error_manager("file extension isn't .rt please correct");
	fd_tester = open(file, O_RDONLY);
	if (fd_tester < 0)
		error_manager("invalid file please check if it exits");
	close(fd_tester);
}

/*
** Verifica si un valor está dentro de un rango [min, max].
** Parámetros:
**   - element_to_check: valor a verificar
**   - minmun_value: límite inferior del rango (inclusivo)
**   - maximun_value: límite superior del rango (inclusivo)
** Retorna:
**   - true si está dentro del rango
**   - false si está fuera
*/
bool	if_betwen_values(float element_to_check, float minmun_value,
		float maximun_value)
{
	if (element_to_check > maximun_value || element_to_check < minmun_value)
		return (false);
	return (true);
}

/*
** Parsea una línea de Ambient Light del archivo .rt
** Formato esperado: A <ratio> <r,g,b>
** Ejemplo: A 0.2 255,255,255
** Parámetros:
**   - actual_elem: array de strings (línea spliteada por espacios)
**   - list_to_add: lista donde guardar los datos parseados
** Resultado:
**   - Añade a la lista: [ratio_float, [r_float, g_float, b_float]]
** Validaciones:
**   - ratio: [0.0, 1.0]
**   - rgb: cada componente [0, 255]
** TODO: Actualmente solo imprime errores, debería retornar error o abortar
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
** Parsea una línea de Light (punto de luz) del archivo .rt
** Formato esperado: L <x,y,z> <brightness> <r,g,b>
** Ejemplo: L -40.0,50.0,0.0 0.6 255,255,255
** TODO: IMPLEMENTAR - Actualmente está vacía
** Debe parsear:
**   - Posición (x,y,z)
**   - Brightness ratio [0.0, 1.0]
**   - Color RGB [0, 255]
*/
void	light_parser(void *actual_elem, void *list_to_add)
{
	(void)actual_elem;
	(void)list_to_add;
}

/*
** Parser genérico que itera sobre una lista y aplica una función parser
** Parámetros:
**   - list__to_track: lista con las líneas del archivo (cada nodo es char**)
**   - f: función parser específica (ambient_light_parser, camera_parser, etc)
** Retorna:
**   - Lista con los elementos parseados por la función f
** Funcionamiento:
**   - Recorre toda la lista
**   - Llama a la función f para cada elemento
**   - La función f decide si procesa o ignora cada línea
**   - Permite que múltiples parsers procesen la misma lista
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
** Parsea una línea de Camera del archivo .rt
** Formato esperado: C <x,y,z> <nx,ny,nz> <fov>
** Ejemplo: C -50.0,0,20 0,0,1 70
** Parámetros:
**   - actual_elem: array de strings (línea spliteada)
**   - list_to_add: lista donde guardar los datos parseados
** Resultado:
**   - Añade: [posición(x,y,z), dirección(nx,ny,nz), fov]
** Validaciones:
**   - posición: cualquier valor float
**   - dirección: cada componente [-1.0, 1.0] (vector normalizado)
**   - fov: [0, 180]
** TODO: Debería normalizar el vector de dirección
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
** Asigna los elementos parseados a la estructura parse_primitive_t
** Parámetros:
**   - element_to_conver: lista con todas las líneas del archivo
**   - struct_to_assignate: estructura donde guardar los resultados
** Retorna:
**   - 0 si todo OK
**   - -1 si hubo error
** Funcionamiento:
**   - Parsea ambient light (A)
**   - Parsea camera (C)
** TODO: Añadir parseo de:
**   - Lights (L)
**   - Objetos: Sphere (sp), Plane (pl), Cylinder (cy)
*/
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

/*
** Lee todo el contenido del archivo .rt y lo guarda en una lista
** Parámetros:
**   - file: ruta al archivo .rt
** Retorna:
**   - Lista de listas: cada nodo contiene un char** (línea spliteada)
** Funcionamiento:
**   - Lee línea por línea con get_next_line
**   - Splitea cada línea por espacios
**   - Guarda cada línea spliteada en un nodo de la lista
** Estructura resultante:
**   nodo1->content = ["A", "0.2", "255,255,255"]
**   nodo2->content = ["C", "-50,0,20", "0,0,1", "70"]
**   ...
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
** Libera recursivamente una lista y su contenido
** Parámetros:
**   - list: lista a liberar
** IMPORTANTE: Solo libera el content si es un puntero simple
** Para contenido complejo (listas anidadas), se necesita lógica adicional
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
** Destructor de la estructura parse_primitive_t
** Libera toda la memoria allocada durante el parseo
** Parámetros:
**   - parse: estructura a destruir
** Retorna:
**   - NULL (para facilitar parse = parse_primiteve_destructor(parse))
** Libera:
**   - ambient light (al)
**   - camera
**   - light
**   - object (spheres, planes, cylinders)
*/
void	*parse_primiteve_destructor(parse_primitive_t *parse)
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
** Constructor principal del parser
** Parámetros:
**   - file: ruta al archivo .rt a parsear
** Retorna:
**   - parse_primitive_t* con todos los datos parseados
**   - NULL si hay error
** Proceso:
**   1. Valida el nombre del archivo
**   2. Lee todo el contenido del archivo
**   3. Parsea cada tipo de elemento (A, C, L, objetos)
**   4. Retorna la estructura con los datos
** TODO: Liberar get_file_content después de usarlo (memory leak)
*/
parse_primitive_t	*parse_primiteve_contructor(char *file)
{
	parse_primitive_t	*temp;

	parser_file_name(file);
	temp = ft_calloc(1, sizeof(parse_primitive_t));
	if (!temp)
		return (NULL);
	if (primitive_parse_t_asignation(get_file_content(file), temp) < 0)
	{
		parse_primiteve_destructor(temp);
		return (NULL);
	}
	return (temp);
}
