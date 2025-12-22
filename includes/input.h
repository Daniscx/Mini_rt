/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:28:19 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/21 22:29:36 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef INPUT_H
#define INPUT_H


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
typedef struct s_vec3 t_vec3;
typedef struct s_input
{
	bool			keys[KEY_COUNT];
	bool			mouse_captured;
	void			*selected_obj;
	bool			dragging;
	t_vec3			drag_plane_point;
	t_vec3			drag_plane_normal;
} t_input;

#endif