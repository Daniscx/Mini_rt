/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:10:51 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 20:29:56 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECTS_H
# define OBJECTS_H
#include "hit.h"
#include "ray.h"
typedef struct s_list t_list;
# define EPSILON 0.0001
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* Object type enumeration */
enum objects
{
    Sp,             /* Sphere */
    Cy,             /* Cylinder */
    Pl,             /* Plane */
    Co,             /* Cone */
    Plc,            /* Plane with checkerboard */
	Spt,            /* Sphere with texture */
    NONE_MANAGE,    /* Placeholder for invalid objects */
};

# include "vector.h"
#include "../libft/libft.h"
# include "texture.h"

/* Cylinder object definition */
typedef struct s_cylinder
{
	t_vec3			center;   /* Center position */
	t_vec3			axis;     /* Axis direction */
	float			diameter; /* Width */
	float			height;   /* Length */
	t_vec3			color;    /* RGB color */
}					t_cylinder;

/* Plane object definition */
typedef struct s_plane
{
	t_vec3			point;   /* Point on plane */
	t_vec3			normal;  /* Surface normal */
	t_vec3			color;   /* RGB color */
} t_plane;

/* Sphere object definition */
typedef struct s_sphere
{
	t_vec3			center;   /* Center position */
	float			diameter; /* Diameter */
	t_vec3			color;    /* RGB color */
	t_texture		*texture;  /* Surface texture */
	t_texture		*bump_map; /* Bump map */
}					t_sphere;

/* Cone object definition */
typedef struct s_cone
{
	t_vec3			apex;     /* Tip position */
	t_vec3			axis;     /* Cone axis direction */
	double			angle;    /* Opening angle */
	double			height;   /* Height of cone */
	t_vec3			color;    /* RGB color */
}	t_cone;

/* Function pointer types for object operations */
typedef t_hit (*t_intersec_fn)(t_ray, void *);  /* Ray intersection callback */
typedef t_vec3 (*t_get_xyz)(void *);            /* Get position callback */
typedef void (*t_move_funct)(void *, t_vec3);   /* Move callback */
typedef bool (*t_collision)(t_vec3, void *);    /* Collision test callback */

/* Generic object wrapper with function pointers */
typedef struct s_paraboid 
{
	t_vec3			vertex;    /* Vertex position */
	t_vec3			axis;      /* Axis direction */
	double			a;         /* Paraboloid curve */
	t_vec3			color;     /* RGB color */
} t_paraboid;

typedef struct s_object
{
    enum objects identificator;     /* Object type */
    void        *figure;             /* Actual object data */
    t_intersec_fn intersecction;    /* Ray intersection function */
    t_get_xyz   postion;             /* Get position function */
    t_move_funct movement;           /* Move function */
	t_collision collision;           /* Collision detection function */
	bool		textured;            /* Has texture applied */
	bool		check_board;         /* Has checkerboard pattern */
} t_object;

/* Object creation from parsed data */
t_list **object_list_Constructor(t_list **components); /* Build object list */
t_cylinder *cylinder_constructor(t_list **components, t_object *object); /* Create cylinder */
t_plane *plane_constructor(t_list **components, t_object *object, bool check_board); /* Create plane */
t_sphere *sphere_constructor(t_list **components, t_object *object, bool texture); /* Create sphere */
t_cone *cone_constructor(t_list **components, t_object *object); /* Create cone */

/* Object operations */
t_hit intersect_plane(t_ray ray, void *plane); /* Intersect ray with plane */
bool camera_collides(t_vec3 pos, t_scene *scene); /* Detect camera collision */
void list_of_objects_destructor(t_list **objects); /* Deallocate all objects */
void print_drop_msg(t_object *obj, t_vec3 pos); /* Print object placement message */

#endif