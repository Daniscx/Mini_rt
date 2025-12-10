/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:31:02 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:31:03 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Constructor de la escena principal del raytracer
** Parámetros:
**   - file: ruta al archivo .rt de la escena
** Retorna:
**   - Puntero a scene_t con todos los datos parseados
**   - NULL si hay error
** Funcionamiento:
**   1. Parsea el archivo .rt con parse_primiteve_contructor
**   2. Crea estructura scene_t
**   3. Transfiere los punteros de parsed a scene
**   4. Libera la estructura temporal parsed (no su contenido)
** NOTA: Los punteros (object, light, al, camera) pasan de parsed a scene
**       sin copiar datos, por lo que no se deben liberar dos veces
*/
scene_t *scene_constructor(char *file)
{
	scene_t			*scene;
	parse_primitive_t	*parsed;

	parsed = parse_primiteve_contructor(file);
	if (!parsed)
		return (NULL);
	scene = malloc(sizeof(scene_t));
	if (!scene)
	{
		parse_primiteve_destructor(parsed);
		return (NULL);
	}
	scene->object = parsed->object;
	scene->light = parsed->light;
	scene->al = parsed->al;
	scene->camera = parsed->camera;
	free(parsed);
	return (scene);
}

/*
** Libera recursivamente una lista y su contenido
** Parámetros:
**   - list: lista a liberar
** Comportamiento:
**   - Recorre toda la lista
**   - Libera el content de cada nodo
**   - Libera cada nodo
** IMPORTANTE: Solo libera un nivel de profundidad
**             Para listas anidadas, necesita lógica adicional
*/
static void	free_list_deep(t_list *list)
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
** Destructor de la estructura scene_t
** Libera toda la memoria allocada para la escena
** Parámetros:
**   - scene: estructura de escena a destruir
** Comportamiento:
**   - Libera las listas de objetos (spheres, planes, cylinders)
**   - Libera las listas de luces
**   - Libera ambient light
**   - Libera datos de la cámara
**   - Libera la estructura scene_t misma
** NOTA: Debe llamarse antes de terminar el programa para evitar memory leaks
*/
void scene_destructor(scene_t *scene)
{
	if (!scene)
		return;
	if (scene->object && *scene->object)
		free_list_deep(*scene->object);
	if (scene->object)
		free(scene->object);
	if (scene->light && *scene->light)
		free_list_deep(*scene->light);
	if (scene->light)
		free(scene->light);
	if (scene->al)
		free(scene->al);
	if (scene->camera)
		free(scene->camera);
	free(scene);
}
