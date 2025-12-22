/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 04:11:55 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 01:12:00 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"
#include <math.h>

/*
** Returns the cross product of two vectors (perpendicular vector).
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
** Returns the magnitude (length) of a vector using Euclidean distance.
*/
double	vec3_length(t_vec3 v)
{
	double result;
	
	result = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (isnan(result) || isinf(result))
		return (0.0);
	return (result);
}

/*
** Returns a unit vector (length 1) in the same direction as v.
*/
t_vec3	vec3_normalize(t_vec3 v)
{
	double	len;

	len = vec3_length(v);
	if (len <= 0.0)
		return (vec3_new(0.0, 0.0, 1.0));
	return (vec3_scale(v, 1.0 / len));
}

/*
** Returns component-wise multiplication of two vectors (for color mixing).
*/
t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x * b.x, a.y * b.y, a.z * b.z));
}

/*
** Returns the negation of a vector (all components multiplied by -1).
*/
t_vec3	vec3_negate(t_vec3 v)
{
	return (vec3_new(-v.x, -v.y, -v.z));
}

/*
** Clamps a value between min and max bounds.
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
** Converts a color vector (0.0-1.0 range) to a 32-bit RGB integer.
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
