/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/10 18:24:07 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Calculates the cross product of two vectors.
** Parameters:
**   - a, b: vectors to multiply
** Returns:
**   - Vector perpendicular to both a and b
** Formula:
**   - result.x = a.y*b.z - a.z*b.y
**   - result.y = a.z*b.x - a.x*b.z
**   - result.z = a.x*b.y - a.y*b.x
** Properties:
**   - Result is perpendicular to both vectors
**   - Magnitude = |a| * |b| * sin(θ)
**   - Follows the right-hand rule
** Usage: Calculate plane normals, orthogonal bases for camera
*/
t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

/*
** Calculates the length (magnitude) of a vector.
** Parameters:
**   - v: vector whose length to calculate
** Returns:
**   - Scalar: sqrt(v.x² + v.y² + v.z²)
** Usage: Calculate distances, verify normalization
*/
double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
** Normalizes a vector (converts to unit vector).
** Parameters:
**   - v: vector to normalize
** Returns:
**   - Vector with same direction but length 1.0
**   - Zero vector if original length is 0
** Behavior:
**   - Calculates length
**   - Divides each component by the length
** Usage: Ray directions, surface normals
*/
t_vec3	vec3_normalize(t_vec3 v)
{
	double	len;

	len = vec3_length(v);
	if (len == 0.0)
		return (vec3_new(0.0, 0.0, 0.0));
	return (vec3_scale(v, 1.0 / len));
}

/*
** Component-wise multiplication (for colors).
*/
t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x * b.x, a.y * b.y, a.z * b.z));
}

/*
** Negates a vector (reverses direction).
*/
t_vec3	vec3_negate(t_vec3 v)
{
	return (vec3_new(-v.x, -v.y, -v.z));
}

/*
** Clamps a value between min and max.
*/
double	vec3_clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/*
** Converts vec3 color [0,1] to int 0xRRGGBB format.
*/
int	vec3_to_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(vec3_clamp(color.x, 0.0, 1.0) * 255.0);
	g = (int)(vec3_clamp(color.y, 0.0, 1.0) * 255.0);
	b = (int)(vec3_clamp(color.z, 0.0, 1.0) * 255.0);
	return ((r << 16) | (g << 8) | b);
}
