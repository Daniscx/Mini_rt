/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:46:10 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 14:47:03 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "../includes/vector.h"
# include "../libft/libft.h"

/* Resolution constants */
# define WIDTH_HIGH 4096    /* High resolution width */
# define HEIGHT_HIGH 2160   /* High resolution height */
# define WIDTH_LOW 426      /* Low resolution width */
# define HEIGHT_LOW 240     /* Low resolution height */

/* Camera controls and physics */
# define CAMERA_RADIUS 0.3  /* Collision sphere radius */
# define MOVE_SPEED 0.3     /* Movement speed units/frame */
# define ROT_SPEED 0.05     /* Rotation speed radians/frame */
# define MOUSE_SENS 0.001   /* Mouse look sensitivity */

typedef struct s_minirt t_minirt;

/* Camera viewing parameters */
typedef struct s_camera
{
	t_vec3	position;     /* Camera position in world space */
	t_vec3	direction;    /* Looking direction unit vector */
	t_vec3	right;        /* Right axis for frustum */
	t_vec3	up;           /* Up axis for frustum */
	double	fov;          /* Field of view angle in degrees */
	double	aspect_ratio; /* Width/height ratio */
	double	yaw;          /* Horizontal rotation angle */
	double	pitch;        /* Vertical rotation angle */
}			t_camera;

/* X11 display structures for window management */
typedef struct s_xvar
{
	Display	*display;  /* X11 display connection */
	Window	root;      /* Root window */
	int		screen;    /* Screen number */
}			t_xvar;

typedef struct s_winlist
{
	Window	window;    /* Window ID */
}			t_winlist;

/* Camera operations */
t_camera *camera_constructor(t_list **components); /* Create camera from parsed data */
void camera_destructor(t_camera *camera); /* Free camera structure */
void camera_update_vectors(t_camera *camera); /* Recalculate view axes */
void camera_move(t_camera *camera, t_vec3 offset); /* Translate camera position */
void camera_rotate(t_camera *camera, double yaw_delta, double pitch_delta); /* Rotate view */

/* Event handlers */
int expose_handler(t_minirt *rt); /* Handle window redraw events */
int mouse_press_handler(int btn, int x, int y, t_minirt *rt); /* Handle mouse click */
int mouse_release_handler(int btn, int x, int y, t_minirt *rt); /* Handle mouse release */
int mouse_move_handler(int x, int y, t_minirt *rt); /* Handle mouse movement */
int key_press_handler(int keycode, t_minirt *rt); /* Handle key press */
int key_release_handler(int keycode, t_minirt *rt); /* Handle key release */
int loop_handler(t_minirt *rt); /* Main application loop */
int close_handler(t_minirt *rt); /* Handle window close */
int is_autorepeat_release(t_minirt *rt, int keycode); /* Check for key repeat */

/* Mouse and window utilities */
void handle_mouse_look(t_minirt *rt, int x, int y); /* Update camera from mouse position */
void warp_mouse_center(t_minirt *rt); /* Lock mouse to window center */
void center_window_on_screen(t_minirt *rt); /* Center window on display */
void resize_window(t_minirt *rt, int width, int height); /* Resize rendering buffer */

#endif