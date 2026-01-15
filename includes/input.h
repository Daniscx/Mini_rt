/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:28:19 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/23 19:40:46 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "vector.h"

/* =[ Key State Indices ]=================================================== */
// Array indices for tracking keyboard state in t_input.keys[]

# define KEY_W 0
# define KEY_A 1
# define KEY_S 2
# define KEY_D 3
# define KEY_SPACE 4
# define KEY_SHIFT 5
# define KEY_LEFT 6
# define KEY_RIGHT 7
# define KEY_UP 8
# define KEY_DOWN 9
# define KEY_COUNT 10

/* =[ Input State ]========================================================= */
// Tracks keyboard, mouse states and object selection/dragging info

typedef struct s_input
{
	bool	keys[KEY_COUNT];
	bool	mouse_captured;
	void	*selected_obj;
	bool	dragging;
	t_vec3	drag_plane_point;
	t_vec3	drag_plane_normal;
}	t_input;

/* ========================================================================= */

#endif
