/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:24:24 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/20 22:27:24 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
#define IMAGE_H

/* =[ MLX Image ]=========================================================== */
// MiniLibX image buffer with pixel data and rendering metadata

typedef struct s_img
{
	void			*img_ptr;
	char			*pixels_ptr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_img;



#endif