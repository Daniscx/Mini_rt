/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:12:52 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:17 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minirt.h"

bool	camera_collides(t_vec3 pos, t_scene *scene)
{
	t_list *aux;
	t_object *obj;

	aux = *scene->object;
	while (aux)
	{
		obj = aux->content;
		
		if (obj->collision(pos, obj->figure))
			return (true);
		aux = aux->next;
	}
	return (false);
}
