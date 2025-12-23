/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 02:37:59 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 19:40:58 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "ray.h"

/* =[ Forward Declarations ]================================================ */

typedef struct s_scene		t_scene;
typedef struct s_texture	t_texture;

/* =[ Hit Record ]========================================================== */
// Stores ray-object intersection data: position, normal, color and effects

typedef struct s_hit
{
	bool		hit;
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_vec3		color;
	double		specular;
	bool		checkerboard;
	double		u;
	double		v;
	t_texture	*texture;
	t_texture	*bump_map;
}	t_hit;

/* =[ Intersection Functions ]============================================== */

t_hit	find_closest_hit(t_ray ray, t_scene *scene);
t_hit	hit_new(void);

/* =[ Hit Effects ]========================================================= */

void	apply_hit_effects(t_hit *hit);

/* ========================================================================= */

#endif
