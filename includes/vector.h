/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:27:23 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 14:47:03 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
typedef struct s_list t_list;
# include "math.h"
# include "../libft/libft.h"
# include "stdbool.h"

typedef struct s_vec3
{
    double x;  /* X component */
    double y;  /* Y component */
    double z;  /* Z component */
} t_vec3;

/* Vector construction and creation */
t_vec3 vector_constructor(t_list **cordenates, bool is_rgb); /* Build vector from parsed list */
t_vec3	vec3_new(double x, double y, double z); /* Create vector from components */

/* Vector arithmetic operations */
t_vec3	vec3_add(t_vec3 a, t_vec3 b); /* Vector addition */

t_vec3	vec3_sub(t_vec3 a, t_vec3 b); /* Vector subtraction */

t_vec3	vec3_scale(t_vec3 v, double scalar); /* Scalar multiplication */

/* Vector algebra */
double	vec3_dot(t_vec3 a, t_vec3 b); /* Dot product */
t_vec3	vec3_cross(t_vec3 a, t_vec3 b); /* Cross product */

double	vec3_length(t_vec3 v); /* Vector magnitude */

t_vec3	vec3_normalize(t_vec3 v); /* Unit vector (normalized) */

t_vec3	vec3_mult(t_vec3 a, t_vec3 b); /* Element-wise multiplication */

t_vec3	vec3_negate(t_vec3 v); /* Negate all components */

double	vec3_clamp(double value, double min, double max); /* Constrain value to range */

int	vec3_to_color(t_vec3 color); /* Convert vector to RGB color value */


#endif