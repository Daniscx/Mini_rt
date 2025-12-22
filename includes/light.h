/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:33:38 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 14:48:12 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
#include "../includes/vector.h"
#include "../includes/hit.h"
#include "../libft/libft.h"

/* Visual quality constants */
# define CHECKER_SCALE 2.0      /* Checkerboard pattern size */
# define SPECULAR_EXP 32.0      /* Phong specularity exponent */
# define SPECULAR_STRENGTH 0.5  /* Reflection intensity */

/* Global illumination parameters (optional color bleeding) */
# ifndef COLOR_BLEEDING
#  define COLOR_BLEEDING 0
# endif
# define GI_INTENSITY 0.4  /* Indirect light color transfer strength */
# define GI_SAMPLES 4      /* Rays per pixel for indirect lighting */

/* Light source definition */
typedef struct s_light
{
	t_vec3			position;   /* 3D position of light */
	float			brightness; /* Light intensity (0.0-1.0) */
	t_vec3			color;      /* RGB light color */
} t_light;

/* Light construction and calculations */
t_list **light_list_constructor(t_list **components); /* Build light sources from parsed data */
t_vec3 apply_checkerboard(t_hit *hit); /* Apply checkerboard pattern to surface */
t_vec3 calculate_color_bleeding(t_hit hit, t_scene *scene); /* Calculate indirect global illumination */
t_vec3 calculate_lighting(t_hit hit, t_scene *scene, t_vec3 view_dir); /* Compute lighting at intersection */

#endif