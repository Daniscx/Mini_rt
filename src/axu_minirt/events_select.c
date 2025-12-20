/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:11:16 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_hit	test_object(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, &obj->sphere));
	if (obj->type == OBJ_PLANE)
		return (intersect_plane(ray, &obj->plane));
	if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder(ray, &obj->cylinder));
	if (obj->type == OBJ_CONE)
		return (intersect_cone(ray, &obj->cone));
	return (hit_new());
}

static int	find_object_at_pixel(t_minirt *rt, int x, int y)
{
	t_ray	ray;
	t_hit	closest;
	t_hit	current;
	int		i;

	ray = ray_from_camera(&rt->scene.camera, x, y, &rt->img);
	closest.hit = false;
	closest.t = 1e30;
	i = -1;
	while (++i < rt->scene.object_count)
	{
		current = test_object(ray, &rt->scene.objects[i]);
		if (current.hit && current.t > EPSILON && current.t < closest.t)
		{
			closest = current;
			rt->input.selected_obj = i;
		}
	}
	if (!closest.hit)
		return (-1);
	return (rt->input.selected_obj);
}

static void	select_object(t_minirt *rt, int x, int y)
{
	int			obj_idx;
	t_object	*obj;
	t_vec3		pos;

	obj_idx = find_object_at_pixel(rt, x, y);
	if (obj_idx < 0)
		return ;
	rt->input.dragging = true;
	obj = &rt->scene.objects[obj_idx];
	pos = get_object_center(obj);
	print_grab_msg(obj, pos);
	rt->input.drag_plane_point = pos;
	rt->input.drag_plane_normal = rt->scene.camera.direction;
}

int	mouse_press_handler(int btn, int x, int y, t_minirt *rt)
{
	if (rt->high_res_mode || rt->input.mouse_captured)
		return (0);
	if (btn == 1)
		select_object(rt, x, y);
	return (0);
}

int	mouse_release_handler(int btn, int x, int y, t_minirt *rt)
{
	t_object	*obj;
	t_vec3		pos;

	(void)x;
	(void)y;
	if (rt->high_res_mode)
		return (0);
	if (btn == 1 && rt->input.dragging)
	{
		obj = &rt->scene.objects[rt->input.selected_obj];
		pos = get_object_center(obj);
		print_drop_msg(obj, pos);
		rt->input.dragging = false;
		rt->input.selected_obj = -1;
	}
	return (0);
}
