/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:45:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:10:28 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_hit	hit_new(void)
{
	t_hit	hit;

	hit.hit = false;
	hit.t = INFINITY;
	hit.point = vec3_new(0, 0, 0);
	hit.normal = vec3_new(0, 1, 0);
	hit.color = vec3_new(0, 0, 0);
	hit.specular = 1.0;
	hit.checkerboard = 0;
	hit.u = 0;
	hit.v = 0;
	hit.texture = NULL;
	hit.bump_map = NULL;
	return (hit);
}
