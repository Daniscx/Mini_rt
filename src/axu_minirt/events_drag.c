/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_drag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/19 15:03:35 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_vec3	ray_plane_intersect(t_ray ray, t_vec3 plane_pt, t_vec3 plane_n)
{
	double	denom;
	double	t;
	t_vec3	diff;

	denom = vec3_dot(plane_n, ray.direction);
	if (fabs(denom) < EPSILON)
		return (plane_pt);
	diff = vec3_sub(plane_pt, ray.origin);
	t = vec3_dot(diff, plane_n) / denom;
	if (t < 0)
		return (plane_pt);
	return (ray_at(ray, t));
}

void	handle_object_drag(t_minirt *rt, int x, int y)
{
	t_ray		ray;
	t_vec3		new_pos;
	t_object	*obj;

	if (!rt->input.dragging || rt->input.selected_obj < 0)
		return ;
	ray = ray_from_camera(&rt->scene.camera, x, y, &rt->img);
	new_pos = ray_plane_intersect(ray, rt->input.drag_plane_point,
			rt->input.drag_plane_normal);
	obj = &rt->scene.objects[rt->input.selected_obj];
	move_object(obj, new_pos);
	rt->input.drag_plane_point = new_pos;
	rt->needs_render = true;
}
