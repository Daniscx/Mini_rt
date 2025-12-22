/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 03:56:15 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 14:47:03 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
#include "image.h"
#include "camera.h"

/* Ray definition: origin point and direction vector */
typedef struct s_ray
{
	t_vec3			origin;    /* Starting point of ray */
	t_vec3			direction; /* Direction unit vector */
}					t_ray;

/* Create ray with given origin and direction */
t_ray	ray_new(t_vec3 origin, t_vec3 direction);

/* Calculate point along ray at parameter t (distance) */
t_vec3	ray_at(t_ray ray, double t);

/* Generate ray from camera through pixel (x, y) on screen */
t_ray	ray_from_camera(t_camera *cam, int x, int y, t_img *img);

#endif