/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:30 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_object	*find_object_at_pixel(t_minirt *rt, int x, int y)
{
	t_ray		ray;
	t_hit		closest;
	t_hit		current;
	t_list		*aux;
	t_object	*current_obj;

	ray = ray_from_camera(rt->scene->camera, x, y, &rt->img);
	closest.hit = false;
	closest.t = 1e30;
	current_obj = NULL;
	aux = *rt->scene->object;
	while (aux)
	{
		current_obj = (t_object *)aux->content;
		current = current_obj->intersecction(ray, current_obj->figure);
		if (current.hit && current.t > EPSILON && current.t < closest.t)
		{
			closest = current;
			rt->input.selected_obj = current_obj;
		}
		aux = aux->next;
	}
	if (!closest.hit)
		return (NULL);
	return (rt->input.selected_obj);
}

static void	select_object(t_minirt *rt, int x, int y)
{
	t_object	*obj;
	t_vec3		pos;
	Display		*dpy;
	Window		win;
	int			mask;

	obj = find_object_at_pixel(rt, x, y);
	if (obj == NULL)
		return ;
	rt->input.dragging = true;
	pos = obj->postion(obj->figure);
	print_grab_msg(obj, pos);
	rt->input.drag_plane_point = pos;
	rt->input.drag_plane_normal = rt->scene->camera->direction;
	dpy = ((t_xvar *)rt->mlx)->display;
	win = ((t_winlist *)rt->win)->window;
	mask = ButtonReleaseMask | PointerMotionMask;
	XGrabPointer(dpy, win, True, mask, GrabModeAsync, GrabModeAsync,
		None, None, CurrentTime);
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
	Display		*dpy;

	(void)x;
	(void)y;
	if (rt->high_res_mode)
		return (0);
	if (btn == 1 && rt->input.dragging)
	{
		obj = rt->input.selected_obj;
		pos = obj->postion(obj->figure);
		print_drop_msg(obj, pos);
		rt->input.dragging = false;
		rt->input.selected_obj = NULL;
		dpy = ((t_xvar *)rt->mlx)->display;
		XUngrabPointer(dpy, CurrentTime);
	}
	return (0);
}
