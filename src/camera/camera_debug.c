/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:13:35 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:15 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_camera(t_camera *camera)
{
	if (!camera)
	{
		printf("Camera: NULL\n");
		return ;
	}
	printf("Camera:\n");
	printf("  Position: (X: %.2f, Y: %.2f, Z: %.2f)\n",
		camera->position.x, camera->position.y, camera->position.z);
	printf("  Direction: (X: %.2f, Y: %.2f, Z: %.2f)\n",
		camera->direction.x, camera->direction.y, camera->direction.z);
	printf("  FOV: %.2f\n", camera->fov);
	printf("  Aspect Ratio: %.2f\n", camera->aspect_ratio);
}
