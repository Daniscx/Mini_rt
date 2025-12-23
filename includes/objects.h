/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:10:51 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 02:49:25 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "hit.h"
# include "vector.h"
# include "texture.h"

/* =[ Defines ]=( Math Constants )========================================== */

// Tolerance for floating point comparisons (avoids precision errors)
# define EPSILON 0.0001

// Constant PI for trigonometric calculations
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// Camera collision radius for scene navigation (used in object collisions)
# define CAMERA_RADIUS 0.3

/* =[ Forward Declarations ]================================================ */

typedef struct s_list	t_list;

/* =[ Function Pointer Types ]============================================== */

typedef t_hit			(*t_intersec_fn)(t_ray, void *);
typedef t_vec3			(*t_get_xyz)(void *);
typedef void			(*t_move_funct)(void *, t_vec3);
typedef bool			(*t_collision)(t_vec3, void *);

/* =[ Object Type Identifiers ]============================================= */
// Enumeration of supported 3D primitive types for scene objects

enum e_objects
{
	Sp,
	Cy,
	Pl,
	Co,
	Plc,
	Spt,
	NONE_MANAGE,
};

/* =[ Cylinder ]============================================================ */
// Cylinder primitive with center base, axis direction, diameter and height

typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			axis;
	float			diameter;
	float			height;
	t_vec3			color;
}	t_cylinder;

/* =[ Plane ]=============================================================== */
// Infinite plane defined by a point on the surface and normal vector

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_vec3			color;
}	t_plane;

/* =[ Sphere ]============================================================== */
// Sphere primitive defined by center, diameter, and optional textures

typedef struct s_sphere
{
	t_vec3			center;
	float			diameter;
	t_vec3			color;
	t_texture		*texture;
	t_texture		*bump_map;
}	t_sphere;

/* =[ Cone ]================================================================ */
// Cone primitive with apex point, axis direction, opening angle and height

typedef struct s_cone
{
	t_vec3			apex;
	t_vec3			axis;
	double			angle;
	double			height;
	t_vec3			color;
}	t_cone;

/* =[ Paraboloid ]========================================================== */
// Paraboloid surface with vertex, axis direction and curvature parameter

typedef struct s_paraboid
{
	t_vec3			vertex;
	t_vec3			axis;
	double			a;
	t_vec3			color;
}	t_paraboid;

/* =[ Generic Object ]====================================================== */
// Union-like container for any scene object type with shared properties

typedef struct s_object
{
	enum e_objects	identificator;
	void			*figure;
	t_intersec_fn	intersecction;
	t_get_xyz		postion;
	t_move_funct	movement;
	t_collision		collision;
	bool			textured;
	bool			check_board;
}	t_object;

/* =[ Object List Constructor ]============================================= */

t_list		**object_list_Constructor(t_list **components);

/* =[ Individual Object Constructors ]====================================== */

t_cylinder	*cylinder_constructor(t_list **comp, t_object *object);
t_plane		*plane_constructor(t_list **comp, t_object *obj, bool check);
t_sphere	*sphere_constructor(t_list **comp, t_object *obj, bool textured);
t_cone		*cone_constructor(t_list **components, t_object *object);

/* =[ Object Destructor ]=================================================== */

void		list_of_objects_destructor(t_list **objects);

/* =[ Object Utilities ]==================================================== */

t_vec3		get_object_center(t_object *obj);
void		move_object(t_object *obj, t_vec3 new_center);

/* =[ Intersection Tests ]================================================== */

t_hit		intersect_sphere(t_ray ray, void *sphere);
t_hit		intersect_plane(t_ray ray, void *plane);
t_hit		intersect_cylinder(t_ray ray, void *cy);
t_hit		intersect_cone(t_ray ray, void *co);

#endif
