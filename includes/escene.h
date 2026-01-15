/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escene.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:43:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 20:22:20 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESCENE_H
# define ESCENE_H

# include "parser.h"
# include "ambient_light.h"
# include "light.h"
# include "camera.h"
# include "objects.h"

/* =[ Defines ]=( Application Settings )==================================== */

// Window title displayed in title bar
# define WIN_TITLE "miniRT"

// Directory for saving screenshots
# define SCREENSHOT_DIR "screenshots"

/* =[ Forward Declarations ]================================================ */

typedef struct s_list	t_list;

/* =[ Scene ]=============================================================== */
// Complete scene with camera, lighting setup, and all renderable objects

typedef struct s_scene
{
	t_list			**object;
	t_list			**light;
	t_ambient_light	*al;
	t_camera		*camera;
}	t_scene;

/* =[ Scene Functions ]===================================================== */

t_scene	*escene_constructor(char *file, int *msg);
void	escene_destructor(t_scene *escene);

/* =[ Debug Print Functions ]=============================================== */

void	print_list_of_lights(t_list **lights);
void	print_ambient_light(t_ambient_light *ambient);
void	print_camera(t_camera *camera);
void	print_list_of_objects(t_list **objects);

#endif
