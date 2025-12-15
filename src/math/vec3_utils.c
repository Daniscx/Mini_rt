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
** Calcula el producto cruz (cross product) de dos vectores
** Parámetros:
**   - a, b: vectores a multiplicar
** Retorna:
**   - Vector perpendicular a ambos a y b
** Fórmula:
**   - result.x = a.y*b.z - a.z*b.y
**   - result.y = a.z*b.x - a.x*b.z
**   - result.z = a.x*b.y - a.y*b.x
** Propiedades:
**   - El resultado es perpendicular a ambos vectores
**   - La magnitud = |a| * |b| * sin(θ)
**   - Sigue la regla de la mano derecha
** Uso: Calcular normales de planos, bases ortogonales para cámara
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
** Calcula la longitud (magnitud) de un vector
** Parámetros:
**   - v: vector del cual calcular la longitud
** Retorna:
**   - Escalar: sqrt(v.x² + v.y² + v.z²)
** Uso: Calcular distancias, verificar normalización
*/
double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
** Normaliza un vector (lo convierte en vector unitario)
** Parámetros:
**   - v: vector a normalizar
** Retorna:
**   - Vector con misma dirección pero longitud 1.0
**   - Vector cero si la longitud original es 0
** Funcionamiento:
**   - Calcula longitud
**   - Divide cada componente por la longitud
** Uso: Direcciones de rayos, normales de superficies
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
** Multiplicacion componente a componente (para colores)
*/
t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x * b.x, a.y * b.y, a.z * b.z));
}

/*
** Negar un vector
*/
t_vec3	vec3_negate(t_vec3 v)
{
	return (vec3_new(-v.x, -v.y, -v.z));
}

/*
** Clamp un valor entre min y max
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
** Convertir vec3 color [0,1] a int 0xRRGGBB
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
