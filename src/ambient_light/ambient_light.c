/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:26:51 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 03:21:11 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/ambient_light.h"

t_ambient_light *ambient_light_constructor(t_list **components)
{
    t_ambient_light *result;
    t_list *aux;
    
    result = ft_calloc(1, sizeof(t_ambient_light ));
    aux = *components;
    result->ratio = *(float *)aux->content;
    aux = aux->next;
    result->color = vector_constructor(aux->content, true);
    return(result);
}

void print_ambient_light(t_ambient_light *ambient)
{
    if (!ambient)
    {
        printf("Ambient Light: NULL\n");
        return;
    }
    printf("Ambient Light:\n");
    printf("  Ratio: %.2f\n", ambient->ratio);
    printf("  Color: (R: %.2f, G: %.2f, B: %.2f)\n",  ambient->color.x, ambient->color.y, ambient->color.z);
}

void ambient_light_destructor(t_ambient_light *ambient)
{
    if(!ambient)
        return;
    free(ambient);
}
