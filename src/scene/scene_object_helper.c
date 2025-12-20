/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:05:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:09:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_object	*alloc_new_objects(t_scene *scene)
{
	t_object	*new_objs;
	int			i;

	new_objs = malloc(sizeof(t_object) * (scene->object_count + 1));
	if (!new_objs)
		return (NULL);
	i = -1;
	while (++i < scene->object_count)
		new_objs[i] = scene->objects[i];
	return (new_objs);
}

void	finalize_object(t_scene *scene, t_object *new_objs)
{
	if (scene->objects)
		free(scene->objects);
	scene->objects = new_objs;
	scene->object_count++;
}
