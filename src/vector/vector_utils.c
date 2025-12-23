/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 04:11:55 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:20:34 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/vector.h"

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	vec3_length(t_vec3 v)
{
	double result;
	
	result = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (isnan(result) || isinf(result))
		return (0.0);
	return (result);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	len;

	len = vec3_length(v);
	if (len <= 0.0)
		return (vec3_new(0.0, 0.0, 1.0));
	return (vec3_scale(v, 1.0 / len));
}

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	vec3_negate(t_vec3 v)
{
	return (vec3_new(-v.x, -v.y, -v.z));
}

double	vec3_clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

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
