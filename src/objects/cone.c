/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 05:42:53 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:59 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/objects.h"

static t_hit	cone_body_hit(t_ray ray, t_cone *co, double t, double cos2)
{
	t_hit	hit;
	double	h;
	t_vec3	tip;

	hit = hit_new();
	if (t < EPSILON)
		return (hit);
	tip = vec3_add(co->apex, vec3_scale(co->axis, co->height));
	hit.point = ray_at(ray, t);
	h = vec3_dot(vec3_sub(hit.point, tip), co->axis);
	if (h > 0 || h < -co->height)
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.normal = vec3_sub(hit.point, tip);
	hit.normal = vec3_sub(hit.normal, vec3_scale(co->axis, vec3_dot(hit.normal, co->axis) / cos2));
	hit.normal = vec3_normalize(hit.normal);
	if (vec3_dot(ray.direction, hit.normal) > 0)
		hit.normal = vec3_negate(hit.normal);
	hit.color = co->color;
	hit.specular = 1.0;
	return (hit);
}

static void	calc_cone_coeffs(t_ray ray, t_cone *co, double *coef, double cos2)
{
	t_vec3	tip;
	t_vec3	oc;
	double	dv;
	double	ocv;

	tip = vec3_add(co->apex, vec3_scale(co->axis, co->height));
	oc = vec3_sub(ray.origin, tip);
	dv = vec3_dot(ray.direction, co->axis);
	ocv = vec3_dot(oc, co->axis);
	coef[0] = dv * dv - cos2 * vec3_dot(ray.direction, ray.direction);
	coef[1] = 2.0 * (dv * ocv - cos2 * vec3_dot(ray.direction, oc));
	coef[2] = ocv * ocv - cos2 * vec3_dot(oc, oc);
}

static t_hit	intersect_cone_body(t_ray ray, t_cone *co)
{
	double	cos2;
	double	coef[3];
	double	disc;
	double	t[2];
	t_hit	hits[2];

	cos2 = cos(co->angle * M_PI / 180.0);
	cos2 = cos2 * cos2;
	calc_cone_coeffs(ray, co, coef, cos2);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit_new());
	t[0] = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	t[1] = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	hits[0] = cone_body_hit(ray, co, t[0], cos2);
	hits[1] = cone_body_hit(ray, co, t[1], cos2);
	if (hits[0].hit && hits[1].hit)
	{
		if (hits[0].t < hits[1].t)
			return (hits[0]);
		return (hits[1]);
	}
	if (hits[0].hit)
		return (hits[0]);
	return (hits[1]);
}

static t_hit	intersect_cone_cap(t_ray ray, t_cone *co)
{
	t_hit	hit;
	t_hit	cap_hit;
	t_plane	cap;
	double	dist;
	double	radius;

	hit = hit_new();
	radius = co->height * tan(co->angle * M_PI / 180.0);
	cap.normal = co->axis;
	cap.point = co->apex;
	cap.color = co->color;
	cap_hit = intersect_plane(ray, &cap);
	if (cap_hit.hit)
	{
		dist = vec3_length(vec3_sub(cap_hit.point, co->apex));
		if (dist <= radius)
			hit = cap_hit;
	}
	return (hit);
}

t_hit	intersect_cone(t_ray ray, void *cone)
{
	t_hit	body_hit;
	t_hit	cap_hit;
	t_cone *co;
	
	co = (t_cone *)cone;
	body_hit = intersect_cone_body(ray, co);
	cap_hit = intersect_cone_cap(ray, co);
	if (!body_hit.hit && !cap_hit.hit)
		return (hit_new());
	if (body_hit.hit && (!cap_hit.hit || body_hit.t < cap_hit.t))
		return (body_hit);
	return (cap_hit);
}

static t_vec3 get_cone_center(void *cone)
{
    t_cone *co;
    t_vec3	offset;
    
    co = (t_cone *)cone;
    offset = vec3_scale(co->axis, co->height / 2.0);
	return (vec3_add(co->apex, offset));
}
void move_cone(void *co, t_vec3 new_center)
{
    t_cone *cone;
    t_vec3	offset;
    
    cone = (t_cone *)co;

    offset = vec3_scale(cone->axis, cone->height / 2.0);
	cone->apex = vec3_sub(new_center, offset);
    
}

static bool	collides_cone(t_vec3 pos, void *cone)
{
	t_vec3	to_pos;
	double	proj;
	double	cone_radius;
	t_vec3	closest;
	double	dist;
	double	h;
	t_cone *co;
	
	co = (t_cone *)cone;
	to_pos = vec3_sub(pos, co->apex);
	proj = vec3_dot(to_pos, co->axis);
	if (proj < -CAMERA_RADIUS || proj > co->height + CAMERA_RADIUS)
		return (false);
	h = co->height - proj;
	if (h < 0)
		h = 0;
	else if (h > co->height)
		h = co->height;
	cone_radius = h * tan(co->angle * M_PI / 180.0);
	closest = vec3_add(co->apex, vec3_scale(co->axis, proj));
	dist = vec3_length(vec3_sub(pos, closest));
	return (dist < cone_radius + CAMERA_RADIUS);
}
t_cone  *cone_constructor(t_list **components, t_object *object)
{
    t_cone *result;
    t_list *aux;
    
    aux = *(components);
    result =  ft_calloc(1, sizeof(t_cone));
    result->apex = vector_constructor(aux->content, false);
    aux = aux->next;
    result->axis = vec3_normalize(vector_constructor(aux->content, false));
    aux = aux->next;
    result->angle = *(float *)aux->content;
    aux = aux->next;
    result->height = *(float *)aux->content;
    aux = aux->next;
    result->color = vector_constructor(aux->content, true);
	object->check_board = false;
    object->intersecction = intersect_cone;
    object->postion = get_cone_center;
    object->movement = move_cone;
	object->collision = collides_cone;
	return(result);
}
void cone_print(t_cone *co)
{
	printf("Cone:\n");
	printf(" Apex: (%f, %f, %f)\n", co->apex.x, co->apex.y, co->apex.z);
	printf(" Axis: (%f, %f, %f)\n", co->axis.x, co->axis.y, co->axis.z);
	printf(" Angle: %f\n", co->angle);
	printf(" Height: %f\n", co->height);
	printf(" Color: (%f, %f, %f)\n", co->color.x, co->color.y, co->color.z);
}
