/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:37:23 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 14:48:12 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/light.h"

#include "../includes/escene.h"

t_light *light_constructor(t_list **components)
{
    t_light *result;
    t_list *aux;
    
    result = ft_calloc(1, sizeof(t_light ));
    aux = *components;
    result->position = vector_constructor(aux->content, false);
    aux = aux->next;
    result->brightness = *(float *)aux->content;
    aux = aux->next;
    result->color = vector_constructor(aux->content, true);
    return(result);
}
void light_destructor(t_light *light)
{
	if(!light)
		return;
	free(light);
}
void print_list_of_lights(t_list **lights)
{
	t_list *aux;
	t_light *light;
	int count = 0;

	aux = *lights;
	printf("List of lights:\n");
	while (aux)
	{
		light = (t_light *)aux->content;
		printf(" Light %d: Position(%.2f, %.2f, %.2f), Brightness: %.2f, Color(%.2f, %.2f, %.2f)\n",
			   count,
			   light->position.x, light->position.y, light->position.z,
			   light->brightness,
			   light->color.x, light->color.y, light->color.z);
		aux = aux->next;
		count++;
	}
}
t_list **light_list_constructor(t_list **components)
{
    t_list **result;
    t_list *aux;
    
    result = ft_calloc(1, sizeof(t_list *));
    aux = *(components);
    while(aux)
    {
        ft_lstadd_back(result, ft_lstnew(light_constructor(aux->content)));
        aux = aux->next;
    }
    return(result);
}
t_vec3	apply_checkerboard(t_hit *hit)
{
	int		u;
	int		v;
	t_vec3	dark;

	u = (int)floor(hit->point.x / CHECKER_SCALE);
	v = (int)floor(hit->point.z / CHECKER_SCALE);
	if ((u + v) % 2 == 0)
		return (hit->color);
	dark = vec3_scale(hit->color, 0.3);
	return (dark);
}

bool	is_in_shadow(t_vec3 point, t_vec3 light_dir, double light_dist,
		t_scene *scene)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.origin = vec3_add(point, vec3_scale(light_dir, EPSILON * 10));
	shadow_ray.direction = light_dir;
	hit = find_closest_hit(shadow_ray, scene);
	if (hit.hit && hit.t < light_dist)
		return (true);
	return (false);
}

static t_vec3	calculate_specular(t_hit hit, t_light *light, t_vec3 view_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	double	spec;
	double	dot_nl;

	if (hit.specular <= 0)
		return (vec3_new(0, 0, 0));
	light_dir = vec3_normalize(vec3_sub(light->position, hit.point));
	dot_nl = vec3_dot(hit.normal, light_dir);
	if (dot_nl < 0)
		return (vec3_new(0, 0, 0));
	reflect_dir = vec3_sub(vec3_scale(hit.normal, 2.0 * dot_nl), light_dir);
	reflect_dir = vec3_normalize(reflect_dir);
	spec = vec3_dot(reflect_dir, view_dir);
	if (spec < 0)
		spec = 0;
	spec = pow(spec, SPECULAR_EXP) * SPECULAR_STRENGTH * light->brightness;
	return (vec3_scale(light->color, spec));
}

static t_vec3	calculate_diffuse(t_hit hit, t_light *light, t_scene *scene)
{
	t_vec3	light_dir;
	double	light_dist;
	double	diff;
	t_vec3	diffuse;

	light_dir = vec3_sub(light->position, hit.point);
	light_dist = vec3_length(light_dir);
	light_dir = vec3_normalize(light_dir);
	if (is_in_shadow(hit.point, light_dir, light_dist, scene))
		return (vec3_new(0, 0, 0));
	diff = vec3_dot(hit.normal, light_dir);
	if (diff < 0)
		diff = 0;
	diffuse = vec3_mult(hit.color, light->color);
	return (vec3_scale(diffuse, diff * light->brightness));
}

t_vec3	calculate_lighting(t_hit hit, t_scene *scene, t_vec3 view_dir)
{
	t_vec3	result;
	t_vec3	ambient;
	t_list  *aux;
    t_light *actual_light;

	apply_hit_effects(&hit);
	ambient = vec3_mult(hit.color, scene->al->color);
	ambient = vec3_scale(ambient, scene->al->ratio);
	result = ambient;
    aux = *scene->light;
	while (aux)
	{   actual_light = aux->content;
		result = vec3_add(result, calculate_diffuse(hit,
					actual_light, scene));
		result = vec3_add(result, calculate_specular(hit,
					actual_light, view_dir));
		aux = aux->next;
	}
	if (COLOR_BLEEDING == 1)
		result = vec3_add(result, vec3_mult(hit.color,
					calculate_color_bleeding(hit, scene)));
	return (result);
}
