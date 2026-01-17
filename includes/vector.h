/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:27:23 by dmaestro          #+#    #+#             */
/*   Updated: 2026/01/17 14:22:49 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "../src/aux_libft/include/libft.h"
# include "../linux-minilibx/mlx.h"

/* =[ 3D Vector ]=========================================================== */
// Represents a 3D point or direction with x, y, z components
// ldt_norminette is the distance light in the calc of an object's shadow.

// It was necessary to add this variable to the struct that was NOT directly
// related to "x", "y" and "z" directly to pass the norminette. 

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
	double	ldt_norminette;
}	t_vec3;

/* =[ Vector Constructor ]=================================================== */

t_vec3	vector_constructor(t_list **cordenates, bool is_rgb);

/* =[ Vector Operations ]=================================================== */

t_vec3	vec3_new(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double scalar);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_mult(t_vec3 a, t_vec3 b);
t_vec3	vec3_negate(t_vec3 v);

/* =[ Vector Utilities ]==================================================== */

double	vec3_clamp(double value, double min, double max);
int		vec3_to_color(t_vec3 color);

/* ========================================================================= */

#endif
