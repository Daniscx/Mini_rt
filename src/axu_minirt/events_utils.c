/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 01:41:51 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	is_autorepeat_release(t_minirt *rt, int keycode)
{
	Display	*display;
	XEvent	next;

	display = ((t_xvar *)rt->mlx)->display;
	if (XPending(display))
	{
		XPeekEvent(display, &next);
		if (next.type == KeyPress && next.xkey.keycode == (unsigned int)keycode)
			return (1);
	}
	return (0);
}

int	close_handler(t_minirt *rt)
{
	minirt_cleanup(rt);
	printf("\n\033[0;96mRendering shutdown protocol detected... Finishing rendering!\033[0;0m\n");
	exit(EXIT_SUCCESS);
}

int	expose_handler(t_minirt *rt)
{
	if (rt->high_res_mode && rt->img_high.img_ptr)
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img_high.img_ptr, 0, 0);
	else if (rt->img.img_ptr)
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
	return (0);
}

t_vec3	get_object_center(t_object *obj)
{
	t_vec3	offset;

	if (obj->type == OBJ_SPHERE)
		return (obj->sphere.center);
	if (obj->type == OBJ_PLANE)
		return (obj->plane.point);
	if (obj->type == OBJ_CYLINDER)
	{
		offset = vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2.0);
		return (vec3_add(obj->cylinder.center, offset));
	}
	if (obj->type == OBJ_CONE)
	{
		offset = vec3_scale(obj->cone.axis, obj->cone.height / 2.0);
		return (vec3_add(obj->cone.apex, offset));
	}
	return (vec3_new(0, 0, 0));
}

void	move_object(t_object *obj, t_vec3 new_center)
{
	t_vec3	offset;

	if (obj->type == OBJ_SPHERE)
		obj->sphere.center = new_center;
	else if (obj->type == OBJ_PLANE)
		obj->plane.point = new_center;
	else if (obj->type == OBJ_CYLINDER)
	{
		offset = vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2.0);
		obj->cylinder.center = vec3_sub(new_center, offset);
	}
	else if (obj->type == OBJ_CONE)
	{
		offset = vec3_scale(obj->cone.axis, obj->cone.height / 2.0);
		obj->cone.apex = vec3_sub(new_center, offset);
	}
}
