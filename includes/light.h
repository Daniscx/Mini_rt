/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:33:38 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 02:48:29 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"
# include "hit.h"

/* =[ Defines ]=( Lighting Settings )======================================= */

// Scale of the chessboard pattern in planes (larger = larger squares)
# define CHECKER_SCALE 2.0

// Specular exponent (Phong): higher = more concentrated & brighter reflections
# define SPECULAR_EXP 32.0

// Specular brightness intensity (0.0 = no brightness, 1.0 = maximum)
# define SPECULAR_STRENGTH 0.5

/* =[ Defines ]=( Color Bleeding / GI )===================================== */

// Enable/disable color bleeding at compile time (make cb)
# ifndef COLOR_BLEEDING
#  define COLOR_BLEEDING 0
# endif

// Color bleeding intensity: how much color transfers between surfaces
// Range 0.0-1.0 (0.2 = subtle, 0.5 = visible, 0.8+ = very strong)
# define GI_INTENSITY 0.4

// Color bleeding samples: rays cast per pixel to gather indirect light
// More samples = smoother result (4 = fast, 8 = balanced, 16 = slower)
# define GI_SAMPLES 4

/* =[ Forward Declarations ]================================================ */

typedef struct s_list	t_list;
typedef struct s_scene	t_scene;

/* =[ Point Light ]========================================================= */
// Point light source with 3D position, brightness intensity and RGB color

typedef struct s_light
{
	t_vec3	position;
	float	brightness;
	t_vec3	color;
}	t_light;

/* =[ Light Functions ]===================================================== */

t_list	**light_list_constructor(t_list **components);
void	light_list_destructor(t_list **lights);

/* =[ Lighting Calculations ]=============================================== */

t_vec3	apply_checkerboard(t_hit *hit);
t_vec3	calculate_color_bleeding(t_hit hit, t_scene *scene);
t_vec3	calculate_lighting(t_hit hit, t_scene *scene, t_vec3 view_dir);

#endif
