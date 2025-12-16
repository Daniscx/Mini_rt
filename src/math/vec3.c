/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/10 18:24:07 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Creates a new 3D vector.
** Parameters:
**   - x, y, z: vector components
** Returns:
**   - t_vec3 vector with given values
** Usage: Create positions, directions, RGB colors
*/
t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/*
** Adds two vectors component-wise.
** Parameters:
**   - a, b: vectors to add
** Returns:
**   - Result vector (a.x + b.x, a.y + b.y, a.z + b.z)
** Usage: Translate points, combine directions
*/
t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x + b.x, a.y + b.y, a.z + b.z));
}

/*
** Subtracts two vectors component-wise.
** Parameters:
**   - a, b: vectors to subtract
** Returns:
**   - Result vector (a - b)
** Usage: Calculate direction between two points, distances
*/
t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x - b.x, a.y - b.y, a.z - b.z));
}

/*
** Multiplies a vector by a scalar.
** Parameters:
**   - v: vector to scale
**   - scalar: scaling factor
** Returns:
**   - Result vector (v.x * scalar, v.y * scalar, v.z * scalar)
** Usage: Adjust vector length, scale colors
*/
t_vec3	vec3_scale(t_vec3 v, double scalar)
{
	return (vec3_new(v.x * scalar, v.y * scalar, v.z * scalar));
}

/*
** Calculates the dot product of two vectors.
** Parameters:
**   - a, b: vectors to multiply
** Returns:
**   - Scalar: a.x*b.x + a.y*b.y + a.z*b.z
** Properties:
**   - If a·b = 0 → perpendicular vectors
**   - If a·b > 0 → acute angle
**   - If a·b < 0 → obtuse angle
** Usage: Lighting calculations, projections, angles
*/
double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
