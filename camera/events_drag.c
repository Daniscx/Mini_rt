/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_drag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/22 02:28:14 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

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

	if (!rt->input.dragging || rt->input.selected_obj == NULL)
		return ;
	ray = ray_from_camera(rt->scene->camera, x, y, &rt->img);
	new_pos = ray_plane_intersect(ray, rt->input.drag_plane_point,
			rt->input.drag_plane_normal);
	obj = rt->input.selected_obj;
	obj->movement(obj->figure, new_pos);
	rt->input.drag_plane_point = new_pos;
	rt->needs_render = true;
}
