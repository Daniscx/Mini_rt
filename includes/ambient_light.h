/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:20:12 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 05:05:50 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AMBIENT_LIGHT_H
# define ABIENT_LIGHT_H
typedef struct s_list t_list;
#include "../libft/libft.h"
#include "vector.h"

typedef struct s_ambient_light
{
	float			ratio;
	t_vec3          color;
}					t_ambient_light;

 t_ambient_light *ambient_light_constructor(t_list **components);
 void 		ambient_light_destructor(t_ambient_light *ambient);
#endif