/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:11:28 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	camera_init(t_camera *camera)
{
	camera->position = vec3_new(0.0, 0.0, -5.0);
	camera->direction = vec3_new(0.0, 0.0, 1.0);
	camera->up = vec3_new(0.0, 1.0, 0.0);
	camera->right = vec3_cross(camera->direction, camera->up);
	camera->fov = 60.0;
	camera->aspect_ratio = (double)WIDTH_LOW / (double)HEIGHT_LOW;
	camera->yaw = 0.0;
	camera->pitch = 0.0;
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
