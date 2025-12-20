/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object_sp_pl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:30:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:09:52 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	load_sphere(t_scene *scene, char **args)
{
	t_object	*new_objs;
	int			i;

	if (!args[1] || !args[2] || !args[3])
		return ;
	new_objs = alloc_new_objects(scene);
	if (!new_objs)
		return ;
	i = scene->object_count;
	new_objs[i].type = OBJ_SPHERE;
	new_objs[i].sphere.center = parse_vec3(args[1]);
	new_objs[i].sphere.diameter = ft_atof(args[2]);
	new_objs[i].sphere.color = parse_color(args[3]);
	new_objs[i].sphere.texture = NULL;
	new_objs[i].sphere.bump_map = NULL;
	new_objs[i].checkerboard = 0;
	finalize_object(scene, new_objs);
}

void	load_sphere_textured(t_scene *scene, char **args)
{
	t_object	*new_objs;
	int			i;

	if (!args[1] || !args[2] || !args[3] || !args[4])
		return ;
	new_objs = alloc_new_objects(scene);
	if (!new_objs)
		return ;
	i = scene->object_count;
	new_objs[i].type = OBJ_SPHERE;
	new_objs[i].sphere.center = parse_vec3(args[1]);
	new_objs[i].sphere.diameter = ft_atof(args[2]);
	new_objs[i].sphere.color = parse_color(args[3]);
	new_objs[i].sphere.texture = texture_load_ppm(args[4]);
	if (args[5])
		new_objs[i].sphere.bump_map = texture_load_ppm(args[5]);
	else
		new_objs[i].sphere.bump_map = NULL;
	new_objs[i].checkerboard = 0;
	finalize_object(scene, new_objs);
}

void	load_plane_ex(t_scene *scene, char **args, int checker)
{
	t_object	*new_objs;
	int			i;

	if (!args[1] || !args[2] || !args[3])
		return ;
	new_objs = alloc_new_objects(scene);
	if (!new_objs)
		return ;
	i = scene->object_count;
	new_objs[i].type = OBJ_PLANE;
	new_objs[i].plane.point = parse_vec3(args[1]);
	new_objs[i].plane.normal = vec3_normalize(parse_vec3(args[2]));
	new_objs[i].plane.color = parse_color(args[3]);
	new_objs[i].checkerboard = checker;
	finalize_object(scene, new_objs);
}

void	load_plane(t_scene *scene, char **args)
{
	load_plane_ex(scene, args, 0);
}
