/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_drag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:19 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minirt.h"

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

static bool	clamp_mouse(t_minirt *rt, int *new_x, int *new_y, int margin)
{
	bool	needs_warp;

	needs_warp = false;
	if (*new_x < margin)
	{
		*new_x = margin;
		needs_warp = true;
	}
	else if (*new_x >= rt->img.width - margin)
	{
		*new_x = rt->img.width - margin - 1;
		needs_warp = true;
	}
	if (*new_y < margin)
	{
		*new_y = margin;
		needs_warp = true;
	}
	else if (*new_y >= rt->img.height - margin)
	{
		*new_y = rt->img.height - margin - 1;
		needs_warp = true;
	}
	return (needs_warp);
}

static void	clamp_mouse_to_window(t_minirt *rt, int *x, int *y)
{
	int		new_x;
	int		new_y;
	bool	needs_warp;

	new_x = *x;
	new_y = *y;
	needs_warp = clamp_mouse(rt, &new_x, &new_y, 20);
	if (needs_warp)
	{
		mlx_mouse_move(rt->mlx, rt->win, new_x, new_y);
		*x = new_x;
		*y = new_y;
	}
}

void	handle_object_drag(t_minirt *rt, int x, int y)
{
	t_ray		ray;
	t_vec3		new_pos;
	t_object	*obj;

	if (!rt->input.dragging || rt->input.selected_obj == NULL)
		return ;
	clamp_mouse_to_window(rt, &x, &y);
	ray = ray_from_camera(rt->scene->camera, x, y, &rt->img);
	new_pos = ray_plane_intersect(ray, rt->input.drag_plane_point,
			rt->input.drag_plane_normal);
	obj = rt->input.selected_obj;
	obj->movement(obj->figure, new_pos);
	rt->input.drag_plane_point = new_pos;
	rt->needs_render = true;
}
