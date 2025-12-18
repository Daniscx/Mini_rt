/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:43:47 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/18 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_scene_leg	*scene_constructor(char *file)
{
	t_scene_leg		*scene;
	t_parse_prim	*parsed;

	parsed = parse_primitive_constructor(file);
	if (!parsed)
		return (NULL);
	scene = malloc(sizeof(t_scene_leg));
	if (!scene)
	{
		parse_primitive_destructor(parsed);
		return (NULL);
	}
	scene->object = parsed->object;
	scene->light = parsed->light;
	scene->al = parsed->al;
	scene->camera = parsed->camera;
	free(parsed);
	return (scene);
}

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

void	scene_destructor(t_scene_leg *scene)
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

static void	free_sphere_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->object_count)
	{
		if (scene->objects[i].type == OBJ_SPHERE)
		{
			if (scene->objects[i].sphere.texture)
				texture_free(scene->objects[i].sphere.texture);
			if (scene->objects[i].sphere.bump_map)
				texture_free(scene->objects[i].sphere.bump_map);
		}
		i++;
	}
}

void	scene_free(t_scene *scene)
{
	if (!scene)
		return ;
	free_sphere_textures(scene);
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
