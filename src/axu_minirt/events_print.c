/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/20 03:11:18 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static const char	*get_type_name(t_obj_type type)
{
	if (type == OBJ_SPHERE)
		return ("Sphere");
	if (type == OBJ_PLANE)
		return ("Plane");
	if (type == OBJ_CYLINDER)
		return ("Cylinder");
	if (type == OBJ_CONE)
		return ("Cone");
	return ("Unknown");
}

void	print_grab_msg(t_object *obj, t_vec3 pos)
{
	printf("\n\033[1;34m[TAKEN]\033[0;0m %s at (%.2f, %.2f, %.2f)\n",
		get_type_name(obj->type), pos.x, pos.y, pos.z);
}

void	print_drop_msg(t_object *obj, t_vec3 pos)
{
	printf("\033[1;32m[DROPPED]\033[0;0m %s at (%.2f, %.2f, %.2f)\n",
		get_type_name(obj->type), pos.x, pos.y, pos.z);
}
