/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:20:12 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 02:47:56 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_LIGHT_H
# define AMBIENT_LIGHT_H

# include "vector.h"

/* =[ Forward Declarations ]================================================ */

typedef struct s_list	t_list;

/* =[ Ambient Light ]======================================================= */
// Global ambient illumination with intensity ratio and RGB color

typedef struct s_ambient_light
{
	float	ratio;
	t_vec3	color;
}	t_ambient_light;

/* =[ Ambient Light Functions ]============================================= */

t_ambient_light	*ambient_light_constructor(t_list **components);
void			ambient_light_destructor(t_ambient_light *ambient);

/* ========================================================================= */

#endif
