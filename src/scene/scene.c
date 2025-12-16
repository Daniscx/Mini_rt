/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:43:47 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 10:43:57 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Main scene constructor for the raytracer.
** Parameters:
**   - file: path to the .rt scene file
** Returns:
**   - Pointer to scene_t with all parsed data
**   - NULL on error
** Behavior:
**   1. Parses the .rt file with parse_primiteve_contructor
**   2. Creates scene_t structure
**   3. Transfers pointers from parsed to scene
**   4. Frees temporary parsed structure (not its content)
** NOTE: Pointers (object, light, al, camera) are transferred from parsed
**       to scene without copying data, so they must not be freed twice.
*/
scene_t	*scene_constructor(char *file)
{
	scene_t				*scene;
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
** Recursively frees a list and its content.
** Parameters:
**   - list: list to free
** Behavior:
**   - Iterates through the entire list
**   - Frees the content of each node
**   - Frees each node
** IMPORTANT: Only frees one level deep.
**            Nested lists require additional logic.
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
** Destructor for the scene_t structure.
** Frees all allocated memory for the scene.
** Parameters:
**   - scene: scene structure to destroy
** Behavior:
**   - Frees object lists (spheres, planes, cylinders)
**   - Frees light lists
**   - Frees ambient light
**   - Frees camera data
**   - Frees the scene_t structure itself
** NOTE: Must be called before program termination to avoid memory leaks.
*/
void	scene_destructor(scene_t *scene)
{
	if (!scene)
		return ;
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

/*
** Frees resources from t_scene (new structure).
** Parameters:
**   - scene: pointer to the scene to free
** Behavior:
**   - Frees lights array
**   - Frees objects array
*/
void	scene_free(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->lights)
	{
		free(scene->lights);
		scene->lights = NULL;
	}
	if (scene->objects)
	{
		free(scene->objects);
		scene->objects = NULL;
	}
	scene->light_count = 0;
	scene->object_count = 0;
}

/*
** Converts parsed data to the new t_scene structure.
** NOTE: Currently unused - the program works directly with parsed structures.
**       This function is reserved for future refactoring if needed.
*/
int	scene_from_parse(t_scene *scene, parse_primitive_t *parsed)
{
	(void)scene;
	(void)parsed;
	return (0);
}
