/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shpere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:49:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 18:28:34 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objects.h"

t_hit	intersect_sphere(t_ray ray, void *sphere)
{
	t_hit	hit;
	t_vec3	oc;
	double	coef[3];
	double	disc;
	double	t;
    t_sphere *sp;
    
    sp = (t_sphere *)sphere;
	hit = hit_new();
	oc = vec3_sub(ray.origin, sp->center);
	coef[0] = vec3_dot(ray.direction, ray.direction);
	coef[1] = 2.0 * vec3_dot(oc, ray.direction);
	coef[2] = vec3_dot(oc, oc) - (sp->diameter / 2.0) * (sp->diameter / 2.0);
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit);
	t = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		t = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	if (t < EPSILON)
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = vec3_normalize(vec3_sub(hit.point, sp->center));
	hit.color = sp->color;
	hit.specular = 1.0;
	hit.texture = sp->texture;
	hit.bump_map = sp->bump_map;
	if (hit.texture && hit.bump_map)
		sphere_get_uv(hit.point, sp->center, &hit.u, &hit.v);
	return (hit);
}
static bool	collides_sphere(t_vec3 pos, void  *sphere)
{
	double	dist;
	double	radius;
	t_sphere *sp;

	sp = (t_sphere *)sphere;
	dist = vec3_length(vec3_sub(pos, sp->center));
	radius = sp->diameter / 2.0;
	return (dist < radius + CAMERA_RADIUS);
}
/*static t_texture *get_sphere_texture(void *sp)
{
	t_sphere *sphere;

	sphere = (t_sphere *)sp;
	return (sphere->texture);

}*/
/*static t_texture *get_sphere_bump_map(void *sp)
{
	t_sphere *sphere;

	sphere = (t_sphere *)sp;
	return (sphere->bump_map);
}*/
static  t_vec3  get_sphere_center(void *sp)
{
    t_sphere *sphere;
    
    sphere = (t_sphere *)sp;
    return(sphere->center);
}
static  void    sphere_new_center(void *sp, t_vec3 new_point)
{
    t_sphere *sphere;

    sphere = (t_sphere *)sp;
    sphere->center = new_point;
}
t_sphere *sphere_constructor(t_list **components, t_object *object, bool texture)
{
    t_sphere    *result;
    t_list      *aux;
    aux = *(components);
    
    result = ft_calloc(1, sizeof(t_sphere ));
    
    result->center = vector_constructor(aux->content, false);
    aux = aux->next;
    result->diameter = *(float *)aux->content;
    aux = aux->next;
    result->color = vector_constructor(aux->content, true);
	object->textured = texture;
	if(texture == true)
	{
		aux = aux->next;
		result->texture = texture_load_ppm(aux->content);
		aux = aux->next;
		result->bump_map = texture_load_ppm(aux->content);
		object->identificator = Sp;
	}
	else
	{
		result->texture = NULL;
		result->bump_map = NULL;
	}
	object->check_board = false;
    object->intersecction = intersect_sphere;
    object->movement = sphere_new_center;
    object->postion = get_sphere_center;
	object->collision = collides_sphere;
    return(result);
}
