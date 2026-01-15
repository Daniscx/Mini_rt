/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:37:23 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:20:16 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/light.h"
#include "../../includes/escene.h"

t_light	*light_constructor(t_list **components)
{
	t_light	*result;
	t_list	*aux;

	result = ft_calloc(1, sizeof(t_light));
	aux = *components;
	result->position = vector_constructor(aux->content, false);
	aux = aux->next;
	result->brightness = *(float *)aux->content;
	aux = aux->next;
	result->color = vector_constructor(aux->content, true);
	return (result);
}

void	light_destructor(t_light *light)
{
	if (!light)
		return ;
	free(light);
}

void	light_list_destructor(t_list **lights)
{
	t_list	*aux;
	t_list	*next;

	if (!lights || !*lights)
		return ;
	aux = *lights;
	while (aux)
	{
		next = aux->next;
		light_destructor((t_light *)aux->content);
		free(aux);
		aux = next;
	}
	free(lights);
}

void	print_list_of_lights(t_list **lights)
{
	t_list	*aux;
	t_light	*light;
	int		count;

	count = 0;
	aux = *lights;
	printf("List of lights:\n");
	while (aux)
	{
		light = (t_light *)aux->content;
		printf(" Light %d: Pos(%.2f, %.2f, %.2f), Br: %.2f\n", count,
			light->position.x, light->position.y, light->position.z,
			light->brightness);
		aux = aux->next;
		count++;
	}
}

t_list	**light_list_constructor(t_list **components)
{
	t_list	**result;
	t_list	*aux;

	result = ft_calloc(1, sizeof(t_list *));
	aux = *(components);
	while (aux)
	{
		ft_lstadd_back(result, ft_lstnew(light_constructor(aux->content)));
		aux = aux->next;
	}
	return (result);
}
