/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/21 23:22:57 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static const char	*get_type_name(enum objects type)
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
