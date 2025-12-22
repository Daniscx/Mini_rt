/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:18:15 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 14:47:03 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "math.h"
#include "vector.h"
#ifndef TEXTURE_H
#define TEXTURE_H

/* Bump mapping effect intensity */
# define BUMP_STRENGTH 0.8

struct s_hit;

/* Texture image data structure */
typedef struct s_texture
{
	unsigned char	*data;    /* Pixel data buffer */
	int				width;   /* Image width in pixels */
	int				height;  /* Image height in pixels */
	int				channels; /* Bytes per pixel (usually 3 for RGB) */
}					t_texture;

/* Texture file I/O */
t_texture *texture_load_ppm(const char *filename); /* Load PPM image file */
void texture_free(t_texture *tex); /* Deallocate texture data */

/* Texture sampling and mapping */
t_vec3 texture_sample(t_texture *tex, double u, double v); /* Sample texture at UV coordinates */
void sphere_get_uv(t_vec3 point, t_vec3 center, double *u, double *v); /* Map sphere surface to UV */

/* Texture effects */
t_vec3 apply_bump_map(struct s_hit *hit); /* Apply normal map for surface detail */
t_vec3 apply_texture(struct s_hit *hit); /* Apply color texture to surface */

#endif