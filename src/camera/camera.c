/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:13:35 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:15 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_camera	*camera_constructor(t_list **components)
{
	t_camera	*result;
	t_list		*aux;
	t_vec3		dir;

	result = ft_calloc(1, sizeof(t_camera));
	aux = *components;
	result->position = vector_constructor(aux->content, false);
	aux = aux->next;
	result->direction = vector_constructor(aux->content, false);
	aux = aux->next;
	result->fov = *(float *)aux->content;
	result->up = vec3_new(0.0, 1.0, 0.0);
	result->aspect_ratio = (double)WIDTH_LOW / (double)HEIGHT_LOW;
	dir = vec3_normalize(result->direction);
	result->pitch = asin(dir.y);
	result->yaw = atan2(dir.x, dir.z);
	result->right = vec3_cross(result->direction, result->up);
	camera_update_vectors(result);
	return (result);
}

void	camera_destructor(t_camera *camera)
{
	if (!camera)
		return ;
	free(camera);
}

void	camera_update_vectors(t_camera *camera)
{
	t_vec3	world_up;

	world_up = vec3_new(0.0, 1.0, 0.0);
	if (fabs(vec3_dot(camera->direction, world_up)) > 0.99)
		world_up = vec3_new(0.0, 0.0, 1.0);
	camera->right = vec3_normalize(vec3_cross(camera->direction, world_up));
	camera->up = vec3_normalize(vec3_cross(camera->right, camera->direction));
}

void	camera_move(t_camera *camera, t_vec3 offset)
{
	camera->position = vec3_add(camera->position, offset);
}

void	camera_rotate(t_camera *camera, double yaw_delta, double pitch_delta)
{
	double	cos_pitch;
	double	sin_pitch;
	double	cos_yaw;
	double	sin_yaw;
	double	max_pitch;

	max_pitch = 80.0 * M_PI / 180.0;
	camera->yaw += yaw_delta;
	camera->pitch += pitch_delta;
	if (camera->pitch > max_pitch)
		camera->pitch = max_pitch;
	if (camera->pitch < -max_pitch)
		camera->pitch = -max_pitch;
	cos_pitch = cos(camera->pitch);
	sin_pitch = sin(camera->pitch);
	cos_yaw = cos(camera->yaw);
	sin_yaw = sin(camera->yaw);
	camera->direction.x = cos_pitch * sin_yaw;
	camera->direction.y = sin_pitch;
	camera->direction.z = cos_pitch * cos_yaw;
	camera->direction = vec3_normalize(camera->direction);
	camera_update_vectors(camera);
}
