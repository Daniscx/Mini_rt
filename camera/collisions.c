/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:12:52 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/22 14:48:12 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"


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