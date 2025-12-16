/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/16 16:33:25 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <stdio.h>

int	close_handler(t_minirt *rt)
{
	minirt_cleanup(rt);
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

static int	get_key_index(int keycode)
{
	if (keycode == XK_w || keycode == XK_W)
		return (KEY_W);
	if (keycode == XK_a || keycode == XK_A)
		return (KEY_A);
	if (keycode == XK_s || keycode == XK_S)
		return (KEY_S);
	if (keycode == XK_d || keycode == XK_D)
		return (KEY_D);
	if (keycode == XK_space)
		return (KEY_SPACE);
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		return (KEY_SHIFT);
	if (keycode == XK_Left)
		return (KEY_LEFT);
	if (keycode == XK_Right)
		return (KEY_RIGHT);
	if (keycode == XK_Up)
		return (KEY_UP);
	if (keycode == XK_Down)
		return (KEY_DOWN);
	return (-1);
}

static void	enter_mouse_mode(t_minirt *rt)
{
	rt->input.mouse_captured = true;
	rt->input.first_move = true;
	ft_bzero(rt->input.keys, sizeof(rt->input.keys));
	warp_mouse_center(rt);
	mlx_mouse_hide(rt->mlx, rt->win);
}

int	key_press_handler(int keycode, t_minirt *rt)
{
	int	key_idx;

	if (keycode == XK_Escape)
		close_handler(rt);
	if (rt->high_res_mode)
		return (0);
	if (keycode == XK_p || keycode == XK_P)
		render_high_res(rt);
	else if ((keycode == XK_m || keycode == XK_M) && !rt->input.mouse_captured)
	{
		printf("\033[1;33m[MOUSE MODE]\033[0m Hold M to look around\n\n");
		enter_mouse_mode(rt);
	}
	else
	{
		key_idx = get_key_index(keycode);
		if (key_idx >= 0)
			rt->input.keys[key_idx] = true;
	}
	return (0);
}

int	key_release_handler(int keycode, t_minirt *rt)
{
	int	key_idx;

	if (rt->high_res_mode)
		return (0);
	if ((keycode == XK_m || keycode == XK_M) && rt->input.mouse_captured)
	{
		rt->input.mouse_captured = false;
		mlx_mouse_show(rt->mlx, rt->win);
		return (0);
	}
	key_idx = get_key_index(keycode);
	if (key_idx >= 0)
		rt->input.keys[key_idx] = false;
	return (0);
}

static t_vec3	get_object_center(t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (obj->sphere.center);
	if (obj->type == OBJ_PLANE)
		return (obj->plane.point);
	if (obj->type == OBJ_CYLINDER)
		return (obj->cylinder.center);
	if (obj->type == OBJ_CONE)
		return (obj->cone.apex);
	return (vec3_new(0, 0, 0));
}

static const char	*get_object_name(t_obj_type type)
{
	if (type == OBJ_SPHERE)
		return ("Sphere");
	if (type == OBJ_PLANE)
		return ("Plane");
	if (type == OBJ_CYLINDER)
		return ("Cylinder");
	if (type == OBJ_CONE)
		return ("Cone");
	return ("Unknown");
}

static void	move_object(t_object *obj, t_vec3 new_pos)
{
	if (obj->type == OBJ_SPHERE)
		obj->sphere.center = new_pos;
	else if (obj->type == OBJ_PLANE)
		obj->plane.point = new_pos;
	else if (obj->type == OBJ_CYLINDER)
		obj->cylinder.center = new_pos;
	else if (obj->type == OBJ_CONE)
		obj->cone.apex = new_pos;
}

static int	find_object_at_pixel(t_minirt *rt, int x, int y, double *out_dist)
{
	t_ray	ray;
	t_hit	closest;
	t_hit	current;
	int		i;
	int		best_idx;

	ray = ray_from_camera(&rt->scene.camera, x, y, &rt->img);
	closest.hit = false;
	closest.t = 1e30;
	best_idx = -1;
	i = -1;
	while (++i < rt->scene.object_count)
	{
		if (rt->scene.objects[i].type == OBJ_SPHERE)
			current = intersect_sphere(ray, &rt->scene.objects[i].sphere);
		else if (rt->scene.objects[i].type == OBJ_PLANE)
			current = intersect_plane(ray, &rt->scene.objects[i].plane);
		else if (rt->scene.objects[i].type == OBJ_CYLINDER)
			current = intersect_cylinder(ray, &rt->scene.objects[i].cylinder);
		else if (rt->scene.objects[i].type == OBJ_CONE)
			current = intersect_cone(ray, &rt->scene.objects[i].cone);
		else
			continue ;
		if (current.hit && current.t > EPSILON && current.t < closest.t)
		{
			closest = current;
			best_idx = i;
		}
	}
	if (out_dist)
		*out_dist = closest.t;
	return (best_idx);
}

int	mouse_press_handler(int button, int x, int y, t_minirt *rt)
{
	int			obj_idx;
	double		dist;
	t_object	*obj;
	t_vec3		pos;

	if (rt->high_res_mode || rt->input.mouse_captured)
		return (0);
	if (button == 1)
	{
		obj_idx = find_object_at_pixel(rt, x, y, &dist);
		if (obj_idx >= 0)
		{
			rt->input.selected_obj = obj_idx;
			rt->input.dragging = true;
			obj = &rt->scene.objects[obj_idx];
			pos = get_object_center(obj);
			rt->input.drag_plane_point = pos;
			rt->input.drag_plane_normal = rt->scene.camera.direction;
			printf("\033[1;32m[SELECTED]\033[0m %s at (%.2f, %.2f, %.2f)\n",
				get_object_name(obj->type), pos.x, pos.y, pos.z);
			fflush(stdout);
		}
	}
	return (0);
}

int	mouse_release_handler(int button, int x, int y, t_minirt *rt)
{
	t_object	*obj;
	t_vec3		pos;

	(void)x;
	(void)y;
	if (rt->high_res_mode)
		return (0);
	if (button == 1 && rt->input.dragging)
	{
		obj = &rt->scene.objects[rt->input.selected_obj];
		pos = get_object_center(obj);
		printf("\033[1;34m[MOVED]\033[0m %s to (%.2f, %.2f, %.2f)\n\n",
			get_object_name(obj->type), pos.x, pos.y, pos.z);
		fflush(stdout);
		rt->input.dragging = false;
		rt->input.selected_obj = -1;
	}
	return (0);
}

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

static void	handle_object_drag(t_minirt *rt, int x, int y)
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

static void	handle_mouse_look(t_minirt *rt, int x, int y)
{
	int	dx;
	int	dy;
	int	cx;
	int	cy;

	cx = WIDTH_LOW / 2;
	cy = HEIGHT_LOW / 2;
	if (rt->input.first_move)
	{
		rt->input.first_move = false;
		return ;
	}
	dx = x - cx;
	dy = y - cy;
	if (dx != 0 || dy != 0)
	{
		camera_rotate(&rt->scene.camera, -dx * MOUSE_SENS, -dy * MOUSE_SENS);
		rt->needs_render = true;
	}
	warp_mouse_center(rt);
}

int	mouse_move_handler(int x, int y, t_minirt *rt)
{
	if (rt->high_res_mode)
		return (0);
	if (rt->input.dragging && !rt->input.mouse_captured)
	{
		handle_object_drag(rt, x, y);
		return (0);
	}
	if (rt->input.mouse_captured)
		handle_mouse_look(rt, x, y);
	return (0);
}

static void	process_movement(t_minirt *rt)
{
	t_vec3	move;

	move = vec3_new(0, 0, 0);
	if (rt->input.keys[KEY_W])
		move = vec3_add(move, rt->scene.camera.direction);
	if (rt->input.keys[KEY_S])
		move = vec3_sub(move, rt->scene.camera.direction);
	if (rt->input.keys[KEY_A])
		move = vec3_sub(move, rt->scene.camera.right);
	if (rt->input.keys[KEY_D])
		move = vec3_add(move, rt->scene.camera.right);
	if (rt->input.keys[KEY_SPACE])
		move = vec3_add(move, rt->scene.camera.up);
	if (rt->input.keys[KEY_SHIFT])
		move = vec3_sub(move, rt->scene.camera.up);
	if (vec3_length(move) > EPSILON)
	{
		move = vec3_scale(vec3_normalize(move), MOVE_SPEED);
		camera_move(&rt->scene.camera, move);
		rt->needs_render = true;
	}
}

static void	process_rotation(t_minirt *rt)
{
	double	yaw;
	double	pitch;

	yaw = 0;
	pitch = 0;
	if (rt->input.keys[KEY_LEFT])
		yaw += ROT_SPEED;
	if (rt->input.keys[KEY_RIGHT])
		yaw -= ROT_SPEED;
	if (rt->input.keys[KEY_UP])
		pitch += ROT_SPEED;
	if (rt->input.keys[KEY_DOWN])
		pitch -= ROT_SPEED;
	if (yaw != 0 || pitch != 0)
	{
		camera_rotate(&rt->scene.camera, yaw, pitch);
		rt->needs_render = true;
	}
}

int	loop_handler(t_minirt *rt)
{
	if (rt->high_res_mode)
		return (0);
	process_movement(rt);
	process_rotation(rt);
	if (rt->needs_render)
	{
		render_scene(rt);
		rt->needs_render = false;
	}
	return (0);
}
