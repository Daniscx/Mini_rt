/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collides.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:12:52 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 16:13:11 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static bool	collides_sphere(t_vec3 pos, t_sphere *sp)
{
	double	dist;
	double	radius;

	dist = vec3_length(vec3_sub(pos, sp->center));
	radius = sp->diameter / 2.0;
	return (dist < radius + CAMERA_RADIUS);
}

static bool	collides_cylinder(t_vec3 pos, t_cylinder *cy)
{
	t_vec3	to_pos;
	double	proj;
	t_vec3	closest;
	double	dist;
	double	radius;

	to_pos = vec3_sub(pos, cy->center);
	proj = vec3_dot(to_pos, cy->axis);
	if (proj < -CAMERA_RADIUS || proj > cy->height + CAMERA_RADIUS)
		return (false);
	closest = vec3_add(cy->center, vec3_scale(cy->axis, proj));
	dist = vec3_length(vec3_sub(pos, closest));
	radius = cy->diameter / 2.0;
	return (dist < radius + CAMERA_RADIUS);
}

static bool	collides_cone(t_vec3 pos, t_cone *co)
{
	t_vec3	to_pos;
	double	proj;
	double	cone_radius;
	t_vec3	closest;
	double	dist;

	to_pos = vec3_sub(pos, co->apex);
	proj = vec3_dot(to_pos, co->axis);
	if (proj < -CAMERA_RADIUS || proj > co->height + CAMERA_RADIUS)
		return (false);
	cone_radius = proj * tan(co->angle * M_PI / 180.0);
	if (cone_radius < 0)
		cone_radius = 0;
	closest = vec3_add(co->apex, vec3_scale(co->axis, proj));
	dist = vec3_length(vec3_sub(pos, closest));
	return (dist < cone_radius + CAMERA_RADIUS);
}

bool	camera_collides(t_vec3 pos, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->object_count)
	{
		if (scene->objects[i].type == OBJ_SPHERE
			&& collides_sphere(pos, &scene->objects[i].sphere))
			return (true);
		if (scene->objects[i].type == OBJ_CYLINDER
			&& collides_cylinder(pos, &scene->objects[i].cylinder))
			return (true);
		if (scene->objects[i].type == OBJ_CONE
			&& collides_cone(pos, &scene->objects[i].cone))
			return (true);
		i++;
	}
	return (false);
}
