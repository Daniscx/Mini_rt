/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:28 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static const char	*get_type_name(enum e_objects type)
{
	if (type == Sp)
		return ("Sphere");
	if (type == Pl)
		return ("Plane");
	if (type == Cy)
		return ("Cylinder");
	if (type == Co)
		return ("Cone");
	return ("Unknown");
}

void	print_grab_msg(t_object *obj, t_vec3 pos)
{
	printf("\n\033[1;34m[TAKEN]\033[0;0m %s at (%.2f, %.2f, %.2f)\n",
		get_type_name(obj->identificator), pos.x, pos.y, pos.z);
}

void	print_drop_msg(t_object *obj, t_vec3 pos)
{
	printf("\033[1;32m[DROPPED]\033[0;0m %s at (%.2f, %.2f, %.2f)\n",
		get_type_name(obj->identificator), pos.x, pos.y, pos.z);
}
