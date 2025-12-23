/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:18:15 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 02:55:53 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "vector.h"

/* =[ Defines ]============================================================= */

# define BUMP_STRENGTH 0.8

/* =[ Forward Declarations ]================================================ */

struct	s_hit;

/* =[ Texture ]============================================================= */
// Stores loaded PPM image data for texture mapping on surfaces

typedef struct s_texture
{
	unsigned char	*data;
	int				width;
	int				height;
	int				channels;
}	t_texture;

/* =[ Texture Functions ]=================================================== */

t_texture	*texture_load_ppm(const char *filename);
void		texture_free(t_texture *tex);
t_vec3		texture_sample(t_texture *tex, double u, double v);

/* =[ UV Mapping ]========================================================== */

void		sphere_get_uv(t_vec3 point, t_vec3 center, double *u, double *v);
t_vec3		apply_bump_map(struct s_hit *hit);
t_vec3		apply_texture(struct s_hit *hit);

/* ========================================================================= */

#endif
