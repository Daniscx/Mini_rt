/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object_cy_co.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:03:50 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:09:46 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	load_cylinder(t_scene *scene, char **args)
{
	t_object	*new_objs;
	int			i;

	if (!args[1] || !args[2] || !args[3] || !args[4] || !args[5])
		return ;
	new_objs = alloc_new_objects(scene);
	if (!new_objs)
		return ;
	i = scene->object_count;
	new_objs[i].type = OBJ_CYLINDER;
	new_objs[i].cylinder.center = parse_vec3(args[1]);
	new_objs[i].cylinder.axis = vec3_normalize(parse_vec3(args[2]));
	new_objs[i].cylinder.diameter = ft_atof(args[3]);
	new_objs[i].cylinder.height = ft_atof(args[4]);
	new_objs[i].cylinder.color = parse_color(args[5]);
	new_objs[i].checkerboard = 0;
	finalize_object(scene, new_objs);
}

void	load_cone(t_scene *scene, char **args)
{
	t_object	*new_objs;
	int			i;

	if (!args[1] || !args[2] || !args[3] || !args[4] || !args[5])
		return ;
	new_objs = alloc_new_objects(scene);
	if (!new_objs)
		return ;
	i = scene->object_count;
	new_objs[i].type = OBJ_CONE;
	new_objs[i].cone.apex = parse_vec3(args[1]);
	new_objs[i].cone.axis = vec3_normalize(parse_vec3(args[2]));
	new_objs[i].cone.angle = ft_atof(args[3]);
	new_objs[i].cone.height = ft_atof(args[4]);
	new_objs[i].cone.color = parse_color(args[5]);
	new_objs[i].checkerboard = 0;
	finalize_object(scene, new_objs);
}
