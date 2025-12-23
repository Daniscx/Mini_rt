/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:41:42 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 02:15:07 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

/* =[ Usage Message ]======================================================= */

# define PRINT_USAGE "\
\
\033[38;5;208mCompile with: \033[0m\"make cb\" to use the color bleeding mode.\n\033[36m\
Usage: \033[0m./miniRT <scene.rt> [width] [height] [fps]\n\
  scene.rt        - Scene file to load.\n\
  width           - Window width.        (426-4096) [optional]\n\
  height          - Window height.       (240-2160) [optional]\n\
  maximum FPS     - Frames per second.   (24-60)    [optional]\n\033[92m\n\
// - If you want to define the width and height of the window, you must\n\
// enter at least those two parameters.\n\
// - Only once the width and height have been defined can the maximum FPS\n\
// be defined.\n\
// - If you want to leave a value as default but must specify a value,\n\
// you can use 0 or any other number in an invalid range.\033[0m\n"

/* =[ Error Messages ]====================================================== */

# define INVALID_OBJECTS "\
\
Invalid number of lights and/or objects. \
There must be at least one object and one light."

/* =[ Default Value Messages ]============================================== */

# define DEF_W "\033[0;31mInvalid width.\033[0m Using default:"
# define DEF_H "\033[0;31mInvalid height.\033[0m Using default:"
# define DEF_FPS "\033[0;31mInvalid frame rate.\033[0m Using default:"

/* =[ Runtime Messages ]==================================================== */

# define M_MODE "\
\n\033[1;33m[MOUSE MODE]\033[0;0m Enabled - Move mouse to look around\n"

# define SD_PROTOCOL "\
\n\033[0;96mRendering shutdown protocol detected... \
Finishing rendering!\033[0;0m\n"

#endif
