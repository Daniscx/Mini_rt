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
** Crea un nuevo vector 3D
** Parámetros:
**   - x, y, z: componentes del vector
** Retorna:
**   - Vector t_vec3 con los valores dados
** Uso: Crear posiciones, direcciones, colores RGB
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
** Suma dos vectores componente a componente
** Parámetros:
**   - a, b: vectores a sumar
** Retorna:
**   - Vector resultado (a.x + b.x, a.y + b.y, a.z + b.z)
** Uso: Trasladar puntos, combinar direcciones
*/
t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x + b.x, a.y + b.y, a.z + b.z));
}

/*
** Resta dos vectores componente a componente
** Parámetros:
**   - a, b: vectores a restar
** Retorna:
**   - Vector resultado (a - b)
** Uso: Calcular dirección entre dos puntos, distancias
*/
t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x - b.x, a.y - b.y, a.z - b.z));
}

/*
** Multiplica un vector por un escalar
** Parámetros:
**   - v: vector a escalar
**   - scalar: factor de escala
** Retorna:
**   - Vector resultado (v.x * scalar, v.y * scalar, v.z * scalar)
** Uso: Ajustar longitud de vectores, escalar colores
*/
t_vec3	vec3_scale(t_vec3 v, double scalar)
{
	return (vec3_new(v.x * scalar, v.y * scalar, v.z * scalar));
}

/*
** Calcula el producto punto (dot product) de dos vectores
** Parámetros:
**   - a, b: vectores a multiplicar
** Retorna:
**   - Escalar: a.x*b.x + a.y*b.y + a.z*b.z
** Propiedades:
**   - Si a·b = 0 → vectores perpendiculares
**   - Si a·b > 0 → ángulo agudo
**   - Si a·b < 0 → ángulo obtuso
** Uso: Cálculos de iluminación, proyecciones, ángulos
*/
double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
