/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:46:10 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 02:47:59 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

/* =[ Defines ]=( Window Resolution )======================================= */

# define WIDTH_HIGH 4096
# define HEIGHT_HIGH 2160

# define WIDTH_LOW 426
# define HEIGHT_LOW 240

/* =[ Defines ]=( Camera Movement )========================================= */

// Camera collision radius for scene navigation
# define CAMERA_RADIUS 0.3

// Movement speed for WASD controls
# define MOVE_SPEED 0.3

// Rotation speed for arrow keys
# define ROT_SPEED 0.05

// Mouse sensitivity for look around
# define MOUSE_SENS 0.001

/* =[ Forward Declarations ]================================================ */

typedef struct s_minirt	t_minirt;
typedef struct s_list	t_list;

/* =[ X11 Internal Structures ]============================================= */
// X11 display and window structures for low-level window management

typedef struct s_xvar
{
	Display	*display;
	Window	root;
	int		screen;
}	t_xvar;

typedef struct s_winlist
{
	Window	window;
}	t_winlist;

/* =[ Camera ]============================================================== */
// Virtual camera with position, orientation vectors, FOV and rotation angles

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	t_vec3	right;
	t_vec3	up;
	double	fov;
	double	aspect_ratio;
	double	yaw;
	double	pitch;
}	t_camera;

/* =[ Camera Operations ]=================================================== */

t_camera	*camera_constructor(t_list **components);
void		camera_destructor(t_camera *camera);
void		camera_update_vectors(t_camera *camera);
void		camera_move(t_camera *camera, t_vec3 offset);
void		camera_rotate(t_camera *cam, double yaw_delta, double pitch_delta);
bool		camera_collides(t_vec3 pos, t_scene *scene);

/* =[ Event Handlers ]====================================================== */

int			expose_handler(t_minirt *rt);
int			mouse_press_handler(int btn, int x, int y, t_minirt *rt);
int			mouse_release_handler(int btn, int x, int y, t_minirt *rt);
int			mouse_move_handler(int x, int y, t_minirt *rt);
int			key_press_handler(int keycode, t_minirt *rt);
int			key_release_handler(int keycode, t_minirt *rt);
int			loop_handler(t_minirt *rt);
int			close_handler(t_minirt *rt);

/* =[ Input Utilities ]===================================================== */

int			is_autorepeat_release(t_minirt *rt, int keycode);
void		handle_mouse_look(t_minirt *rt, int x, int y);
void		warp_mouse_center(t_minirt *rt);

/* =[ Window Functions ]==================================================== */

void		center_window_on_screen(t_minirt *rt);
void		resize_window(t_minirt *rt, int width, int height);

#endif
