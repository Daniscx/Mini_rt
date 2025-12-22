/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escene.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:43:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 17:52:47 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESCENE_H
#define ESCENE_H

#include "../escene/parser.h"
#include "ambient_light.h"
#include "light.h"
#include "camera.h"
#include "objects.h"
#include "libft.h"

# define WIN_TITLE "miniRT"
# define SCREENSHOT_DIR "screenshots"

/* Complete scene definition with all rendering elements */
typedef struct s_scene
{
    t_list **object;          /* List of objects in scene */
    t_list **light;           /* List of light sources */
    t_ambient_light *al;      /* Ambient lighting */
    t_camera *camera;         /* Camera for viewing */
} t_scene;

/* Scene construction and destruction */
t_scene *escene_constructor(char *file); /* Load scene from .rt file */
void escene_destructor(t_scene *escene); /* Free entire scene and resources */

/* Debug output functions */
void print_list_of_lights(t_list **lights); /* Debug: print light sources */
void print_ambient_light(t_ambient_light *ambient); /* Debug: print ambient light */
void print_camera(t_camera *camera); /* Debug: print camera parameters */
void print_list_of_objects(t_list **objects); /* Debug: print objects */

#endif
