/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 02:37:59 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 14:48:33 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
#define HIT_H

#include <stdbool.h>
#include "ray.h"

typedef struct s_scene t_scene;
typedef struct s_texture t_texture;

/* Intersection data from ray-object collision */
typedef struct s_hit
{
	bool			hit;        /* Whether collision occurred */
	double			t;          /* Distance along ray to hit point */
	t_vec3			point;      /* 3D position of intersection */
	t_vec3			normal;     /* Surface normal at intersection */
	t_vec3			color;      /* Base surface color */
	double			specular;   /* Specularity/glossiness factor */
	bool			checkerboard; /* Enable checkerboard pattern */
	double			u;          /* Texture coordinate U */
	double			v;          /* Texture coordinate V */
	t_texture		*texture;   /* Surface texture */
	t_texture		*bump_map;  /* Bump/normal map for detail */
} t_hit;

/* Find nearest intersection along ray in scene */
t_hit	find_closest_hit(t_ray ray, t_scene *scene);

/* Initialize empty hit structure */
t_hit	hit_new(void);

/* Apply texture, bump mapping, and visual effects to hit */
void	apply_hit_effects(t_hit *hit);

#endif