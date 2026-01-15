/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:35:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:14:03 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

t_vec3	vector_constructor(t_list **cordinates, bool is_rgb)
{
	t_list	*aux;
	double	x;
	double	y;
	double	z;

	aux = *cordinates;
	x = *(float *)aux->content;
	if (is_rgb == true)
		x /= 255;
	aux = aux->next;
	y = *(float *)aux->content;
	if (is_rgb == true)
		y /= 255;
	aux = aux->next;
	z = *(float *)aux->content;
	if (is_rgb == true)
		z /= 255;
	return (vec3_new(x, y, z));
}

t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_scale(t_vec3 v, double scalar)
{
	return (vec3_new(v.x * scalar, v.y * scalar, v.z * scalar));
}
