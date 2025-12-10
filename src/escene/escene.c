/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escene.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:31:02 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:31:03 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

/*
** Constructor de la escena principal del raytracer
** Parámetros:
**   - file: ruta al archivo .rt de la escena
** Retorna:
**   - Puntero a escene_t con todos los datos parseados
**   - NULL si hay error
** Funcionamiento:
**   1. Parsea el archivo .rt con parse_primiteve_contructor
**   2. Crea estructura escene_t
**   3. Transfiere los punteros de parsed a escene
**   4. Libera la estructura temporal parsed (no su contenido)
** NOTA: Los punteros (object, light, al, camera) pasan de parsed a escene
**       sin copiar datos, por lo que no se deben liberar dos veces
*/
escene_t *escene_constructor(char *file)
{
	escene_t			*escene;
	parse_primitive_t	*parsed;

	parsed = parse_primiteve_contructor(file);
	if (!parsed)
		return (NULL);
	escene = malloc(sizeof(escene_t));
	if (!escene)
	{
		parse_primiteve_destructor(parsed);
		return (NULL);
	}
	escene->object = parsed->object;
	escene->light = parsed->light;
	escene->al = parsed->al;
	escene->camera = parsed->camera;
	free(parsed);
	return (escene);
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
** Destructor de la estructura escene_t
** Libera toda la memoria allocada para la escena
** Parámetros:
**   - escene: estructura de escena a destruir
** Comportamiento:
**   - Libera las listas de objetos (spheres, planes, cylinders)
**   - Libera las listas de luces
**   - Libera ambient light
**   - Libera datos de la cámara
**   - Libera la estructura escene_t misma
** NOTA: Debe llamarse antes de terminar el programa para evitar memory leaks
*/
void escene_destructor(escene_t *escene)
{
	if (!escene)
		return;
	if (escene->object && *escene->object)
		free_list_deep(*escene->object);
	if (escene->object)
		free(escene->object);
	if (escene->light && *escene->light)
		free_list_deep(*escene->light);
	if (escene->light)
		free(escene->light);
	if (escene->al)
		free(escene->al);
	if (escene->camera)
		free(escene->camera);
	free(escene);
}
