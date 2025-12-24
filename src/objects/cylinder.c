/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:47:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:19:27 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/objects.h"

static t_hit	intersect_cylinder_body(t_ray ray, t_cylinder *cy)
{
	t_hit	hit;
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	coef[3];
	double	disc;
	double	t;
	double	h;

	hit = hit_new();
	oc = vec3_sub(ray.origin, cy->center);
	d_perp = vec3_sub(ray.direction, vec3_scale(cy->axis, vec3_dot(ray.direction, cy->axis)));
	oc_perp = vec3_sub(oc, vec3_scale(cy->axis, vec3_dot(oc, cy->axis)));
	coef[0] = vec3_dot(d_perp, d_perp);
	coef[1] = 2.0 * vec3_dot(d_perp, oc_perp);
	coef[2] = vec3_dot(oc_perp, oc_perp) - (cy->diameter / 2.0) * (cy->diameter / 2.0);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit);
	t = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		t = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		return (hit);
	hit.point = ray_at(ray, t);
	h = vec3_dot(vec3_sub(hit.point, cy->center), cy->axis);
	if (h < 0 || h > cy->height)
		return (hit_new());
	hit.hit = true;
	hit.t = t;
	hit.normal = vec3_normalize(vec3_sub(vec3_sub(hit.point, cy->center), vec3_scale(cy->axis, h)));
	hit.color = cy->color;
	hit.specular = 1.0;
	return (hit);
}

static t_hit	intersect_cylinder_caps(t_ray ray, t_cylinder *cy)
{
	t_hit		hit;
	t_hit		cap_hit;
	t_plane		cap;
	double		dist;

	hit = hit_new();
	cap.normal = cy->axis;
	cap.point = cy->center;
	cap.color = cy->color;
	cap_hit = intersect_plane(ray, &cap);
	if (cap_hit.hit)
	{
		dist = vec3_length(vec3_sub(cap_hit.point, cy->center));
		if (dist <= cy->diameter / 2.0 && cap_hit.t < hit.t)
			hit = cap_hit;
	}
	cap.point = vec3_add(cy->center, vec3_scale(cy->axis, cy->height));
	cap_hit = intersect_plane(ray, &cap);
	if (cap_hit.hit)
	{
		dist = vec3_length(vec3_sub(cap_hit.point, cap.point));
		if (dist <= cy->diameter / 2.0 && cap_hit.t < hit.t)
			hit = cap_hit;
	}
	return (hit);
}

t_hit	intersect_cylinder(t_ray ray, void  *cylinder)
{
	t_cylinder	*cy;
	t_hit	body_hit;
	t_hit	caps_hit;

	cy = (t_cylinder *)cylinder;
	body_hit = intersect_cylinder_body(ray, cy);
	caps_hit = intersect_cylinder_caps(ray, cy);
	if (!body_hit.hit && !caps_hit.hit)
		return (hit_new());
	if (body_hit.hit && (!caps_hit.hit || body_hit.t < caps_hit.t))
		return (body_hit);
	return (caps_hit);
}

t_vec3  get_cylinder_body_center(void *cy)
{
    t_cylinder *cylinder;
    t_vec3 offset;

    cylinder = (t_cylinder *)cy;
    offset = vec3_scale(cylinder->axis, cylinder->height / 2.0);
	return (vec3_add(cylinder->center, offset));
}

void  move_cylinder(void *cy, t_vec3 new_center)
{
    t_vec3 offset;
    t_cylinder *cylinder;
    
    cylinder = (t_cylinder *)cy;
    offset = vec3_scale(cylinder->axis, cylinder->height / 2.0);
	cylinder->center = vec3_sub(new_center, offset);
}

static bool	collides_cylinder(t_vec3 pos, void *cylinder)
{
	t_vec3	to_pos;
	double	proj;
	t_vec3	closest;
	double	dist;
	double	radius;
	t_cylinder *cy;

	cy = (t_cylinder *)cylinder;
	to_pos = vec3_sub(pos, cy->center);
	proj = vec3_dot(to_pos, cy->axis);
	if (proj < -CAMERA_RADIUS || proj > cy->height + CAMERA_RADIUS)
		return (false);
	closest = vec3_add(cy->center, vec3_scale(cy->axis, proj));
	dist = vec3_length(vec3_sub(pos, closest));
	radius = cy->diameter / 2.0;
	return (dist < radius + CAMERA_RADIUS);
}

t_cylinder *cylinder_constructor(t_list **components, t_object *object)
{
    t_cylinder  *result;
    t_list *aux;
      
    aux = *(components);
    result =  ft_calloc(1, sizeof(t_cylinder ));
    result->center = vector_constructor(aux->content, false);
    aux = aux->next;
    result->axis = vec3_normalize(vector_constructor(aux->content, false));
    aux = aux->next;
    result->diameter = *(float *)aux->content;
    aux = aux->next;
    result->height = *(float *)aux->content;
    aux = aux->next;
    result->color = vector_constructor(aux->content, true);
    object->intersecction = intersect_cylinder;
    object->postion = get_cylinder_body_center;
    object->movement = move_cylinder;
	object->check_board = false;
	object->collision = collides_cylinder;
    return(result);    
}

void cylinder_print(t_cylinder *cylinder)
{
	printf("Cylinder:\n");
	printf(" Center: (%.2f, %.2f, %.2f)\n", cylinder->center.x, cylinder->center.y, cylinder->center.z);
	printf(" Axis: (%.2f, %.2f, %.2f)\n", cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
	printf(" Diameter: %.2f\n", cylinder->diameter);
	printf(" Height: %.2f\n", cylinder->height);
	printf(" Color: (%.2f, %.2f, %.2f)\n", cylinder->color.x, cylinder->color.y, cylinder->color.z);
}
