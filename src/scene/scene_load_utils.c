/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_load_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:30:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:06:14 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	parse_vec3(char *str)
{
	char	**split;
	t_vec3	v;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free_double_pointer(split);
		return (vec3_new(0, 0, 0));
	}
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	free_double_pointer(split);
	return (v);
}

t_vec3	parse_color(char *str)
{
	t_vec3	c;

	c = parse_vec3(str);
	c.x /= 255.0;
	c.y /= 255.0;
	c.z /= 255.0;
	return (c);
}

void	load_ambient(t_scene *scene, char **args)
{
	if (!args[1] || !args[2])
		return ;
	scene->ambient.ratio = ft_atof(args[1]);
	scene->ambient.color = parse_color(args[2]);
}

void	load_camera(t_scene *scene, char **args)
{
	t_vec3	up;

	if (!args[1] || !args[2] || !args[3])
		return ;
	scene->camera.position = parse_vec3(args[1]);
	scene->camera.direction = vec3_normalize(parse_vec3(args[2]));
	scene->camera.fov = ft_atof(args[3]);
	scene->camera.aspect_ratio = (double)WIDTH_LOW / (double)HEIGHT_LOW;
	scene->camera.yaw = atan2(scene->camera.direction.x, scene->camera.direction.z);
	scene->camera.pitch = asin(scene->camera.direction.y);
	up = vec3_new(0, 1, 0);
	if (fabs(vec3_dot(scene->camera.direction, up)) > 0.99)
		up = vec3_new(0, 0, 1);
	scene->camera.right = vec3_normalize(vec3_cross(scene->camera.direction, up));
	scene->camera.up = vec3_cross(scene->camera.right, scene->camera.direction);
}

void	load_light(t_scene *scene, char **args)
{
	t_light	*new_lights;
	int		i;

	if (!args[1] || !args[2])
		return ;
	new_lights = malloc(sizeof(t_light) * (scene->light_count + 1));
	if (!new_lights)
		return ;
	i = 0;
	while (i < scene->light_count)
	{
		new_lights[i] = scene->lights[i];
		i++;
	}
	new_lights[i].position = parse_vec3(args[1]);
	new_lights[i].brightness = ft_atof(args[2]);
	if (args[3])
		new_lights[i].color = parse_color(args[3]);
	else
		new_lights[i].color = vec3_new(1, 1, 1);
	if (scene->lights)
		free(scene->lights);
	scene->lights = new_lights;
	scene->light_count++;
}
