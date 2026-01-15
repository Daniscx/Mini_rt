/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 03:56:15 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 19:40:16 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "image.h"

/* =[ Forward Declarations ]================================================ */

typedef struct s_camera	t_camera;

/* =[ Ray ]================================================================= */
// Represents a ray with origin point and normalized direction vector

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

/* =[ Ray Operations ]====================================================== */

t_ray	ray_new(t_vec3 origin, t_vec3 direction);
t_vec3	ray_at(t_ray ray, double t);
t_ray	ray_from_camera(t_camera *cam, int x, int y, t_img *img);

/* ========================================================================= */

#endif
