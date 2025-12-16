/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 10:44:01 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Parses a comma-separated string into a 3D vector.
*/
static t_vec3	parse_vec3(char *str)
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

/*
** Parses RGB color string (0-255) and converts to normalized (0-1) vector.
*/
static t_vec3	parse_color(char *str)
{
	t_vec3	c;

	c = parse_vec3(str);
	c.x /= 255.0;
	c.y /= 255.0;
	c.z /= 255.0;
	return (c);
}

/*
** Loads ambient light from parsed arguments into scene structure.
*/
static void	load_ambient(t_scene *scene, char **args)
{
	if (!args[1] || !args[2])
		return ;
	scene->ambient.ratio = ft_atof(args[1]);
	scene->ambient.color = parse_color(args[2]);
}

/*
** Loads camera from parsed arguments. Calculates orientation vectors.
*/
static void	load_camera(t_scene *scene, char **args)
{
	t_vec3	up;

	if (!args[1] || !args[2] || !args[3])
		return ;
	scene->camera.position = parse_vec3(args[1]);
	scene->camera.direction = vec3_normalize(parse_vec3(args[2]));
	scene->camera.fov = ft_atof(args[3]);
	scene->camera.aspect_ratio = (double)WIDTH_LOW / (double)HEIGHT_LOW;
	scene->camera.yaw = atan2(scene->camera.direction.x,
			scene->camera.direction.z);
	scene->camera.pitch = asin(scene->camera.direction.y);
	up = vec3_new(0, 1, 0);
	if (fabs(vec3_dot(scene->camera.direction, up)) > 0.99)
		up = vec3_new(0, 0, 1);
	scene->camera.right = vec3_normalize(vec3_cross(scene->camera.direction,
				up));
	scene->camera.up = vec3_cross(scene->camera.right, scene->camera.direction);
}

/*
** Loads a point light into the scene. Reallocates lights array.
*/
static void	load_light(t_scene *scene, char **args)
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

/*
** Loads a sphere object into the scene. Reallocates objects array.
*/
static void	load_sphere(t_scene *scene, char **args)
{
	t_object	*new_objs;
	int			i;

	if (!args[1] || !args[2] || !args[3])
		return ;
	new_objs = malloc(sizeof(t_object) * (scene->object_count + 1));
	if (!new_objs)
		return ;
	i = -1;
	while (++i < scene->object_count)
		new_objs[i] = scene->objects[i];
	new_objs[i].type = OBJ_SPHERE;
	new_objs[i].sphere.center = parse_vec3(args[1]);
	new_objs[i].sphere.diameter = ft_atof(args[2]);
	new_objs[i].sphere.color = parse_color(args[3]);
	new_objs[i].checkerboard = 0;
	if (scene->objects)
		free(scene->objects);
	scene->objects = new_objs;
	scene->object_count++;
}

/*
** Loads a plane object with optional checkerboard pattern.
*/
static void	load_plane_ex(t_scene *scene, char **args, int checker)
{
	t_object	*new_objs;
	int			i;

	if (!args[1] || !args[2] || !args[3])
		return ;
	new_objs = malloc(sizeof(t_object) * (scene->object_count + 1));
	if (!new_objs)
		return ;
	i = -1;
	while (++i < scene->object_count)
		new_objs[i] = scene->objects[i];
	new_objs[i].type = OBJ_PLANE;
	new_objs[i].plane.point = parse_vec3(args[1]);
	new_objs[i].plane.normal = vec3_normalize(parse_vec3(args[2]));
	new_objs[i].plane.color = parse_color(args[3]);
	new_objs[i].checkerboard = checker;
	if (scene->objects)
		free(scene->objects);
	scene->objects = new_objs;
	scene->object_count++;
}

/*
** Wrapper for load_plane_ex without checkerboard pattern.
*/
static void	load_plane(t_scene *scene, char **args)
{
	load_plane_ex(scene, args, 0);
}

/*
** Loads a cylinder object into the scene.
*/
static void	load_cylinder(t_scene *scene, char **args)
{
	t_object	*new_objs;
	int			i;

	if (!args[1] || !args[2] || !args[3] || !args[4] || !args[5])
		return ;
	new_objs = malloc(sizeof(t_object) * (scene->object_count + 1));
	if (!new_objs)
		return ;
	i = -1;
	while (++i < scene->object_count)
		new_objs[i] = scene->objects[i];
	new_objs[i].type = OBJ_CYLINDER;
	new_objs[i].cylinder.center = parse_vec3(args[1]);
	new_objs[i].cylinder.axis = vec3_normalize(parse_vec3(args[2]));
	new_objs[i].cylinder.diameter = ft_atof(args[3]);
	new_objs[i].cylinder.height = ft_atof(args[4]);
	new_objs[i].cylinder.color = parse_color(args[5]);
	new_objs[i].checkerboard = 0;
	if (scene->objects)
		free(scene->objects);
	scene->objects = new_objs;
	scene->object_count++;
}

/*
** Loads a cone object into the scene.
*/
static void	load_cone(t_scene *scene, char **args)
{
	t_object	*new_objs;
	int			i;

	if (!args[1] || !args[2] || !args[3] || !args[4] || !args[5])
		return ;
	new_objs = malloc(sizeof(t_object) * (scene->object_count + 1));
	if (!new_objs)
		return ;
	i = -1;
	while (++i < scene->object_count)
		new_objs[i] = scene->objects[i];
	new_objs[i].type = OBJ_CONE;
	new_objs[i].cone.apex = parse_vec3(args[1]);
	new_objs[i].cone.axis = vec3_normalize(parse_vec3(args[2]));
	new_objs[i].cone.angle = ft_atof(args[3]);
	new_objs[i].cone.height = ft_atof(args[4]);
	new_objs[i].cone.color = parse_color(args[5]);
	new_objs[i].checkerboard = 0;
	if (scene->objects)
		free(scene->objects);
	scene->objects = new_objs;
	scene->object_count++;
}

/*
** Processes a single line from .rt file and delegates to appropriate loader.
*/
static void	process_line(t_scene *scene, char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	if (!args || !args[0])
	{
		free_double_pointer(args);
		return ;
	}
	if (ft_strncmp(args[0], "A", 2) == 0)
		load_ambient(scene, args);
	else if (ft_strncmp(args[0], "C", 2) == 0)
		load_camera(scene, args);
	else if (ft_strncmp(args[0], "L", 2) == 0)
		load_light(scene, args);
	else if (ft_strncmp(args[0], "sp", 3) == 0)
		load_sphere(scene, args);
	else if (ft_strncmp(args[0], "plc", 4) == 0)
		load_plane_ex(scene, args, 1);
	else if (ft_strncmp(args[0], "pl", 3) == 0)
		load_plane(scene, args);
	else if (ft_strncmp(args[0], "cy", 3) == 0)
		load_cylinder(scene, args);
	else if (ft_strncmp(args[0], "co", 3) == 0)
		load_cone(scene, args);
	free_double_pointer(args);
}

/*
** Main scene loader. Opens file based on route code, parses all lines.
*/
int	scene_load(t_scene *scene, char *filename, int route)
{
	int		fd;
	char	*line;
	char	*to_open;
	char	*in_open;

	ft_bzero(scene, sizeof(t_scene));
	if (route == 1)
		to_open = ft_strjoin(filename, ".rt");
	else if (route == 2)
	{
		in_open = ft_strjoin(filename, ".rt");
		to_open = ft_strjoin("scenes/", in_open);
	}
	else if (route == 3)
		to_open = ft_strdup(filename);
	else if (route == 4)
		to_open = ft_strjoin("scenes/", filename);
	fd = open(to_open, O_RDONLY);
	if (fd < 0)
	{
		if (route == 2)
			free(in_open);
		free(to_open);
		error_manager("Failed to load scene file.");
	}
	line = get_next_line(fd);
	while (line)
	{
		process_line(scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (scene->light_count == 0 || scene->object_count == 0)
	{
		if (route == 2)
			free(in_open);
		return (free(to_open), -1);
	}
	if (route == 2)
		free(in_open);
	return (free(to_open), 0);
}
