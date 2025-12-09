/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:30:37 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

void	camera_init(t_camera *camera)
{
	camera->position = vec3_new(0.0, 0.0, -5.0);
	camera->direction = vec3_new(0.0, 0.0, 1.0);
	camera->up = vec3_new(0.0, 1.0, 0.0);
	camera->right = vec3_cross(camera->direction, camera->up);
	camera->fov = 60.0;
	camera->aspect_ratio = (double)WIDTH / (double)HEIGHT;
}

void	camera_move(t_camera *camera, t_vec3 offset)
{
	camera->position = vec3_add(camera->position, offset);
}

void	camera_rotate(t_camera *camera, double yaw, double pitch)
{
	double	cos_yaw;
	double	sin_yaw;
	double	cos_pitch;
	double	sin_pitch;
	t_vec3	new_dir;

	cos_yaw = cos(yaw);
	sin_yaw = sin(yaw);
	cos_pitch = cos(pitch);
	sin_pitch = sin(pitch);
	new_dir.x = camera->direction.x * cos_yaw - camera->direction.z * sin_yaw;
	new_dir.z = camera->direction.x * sin_yaw + camera->direction.z * cos_yaw;
	new_dir.y = camera->direction.y * cos_pitch - new_dir.z * sin_pitch;
	new_dir.z = camera->direction.y * sin_pitch + new_dir.z * cos_pitch;
	new_dir.x = new_dir.x;
	camera->direction = vec3_normalize(new_dir);
	camera->right = vec3_normalize(vec3_cross(camera->direction, vec3_new(0.0,
					1.0, 0.0)));
	camera->up = vec3_normalize(vec3_cross(camera->right, camera->direction));
}
