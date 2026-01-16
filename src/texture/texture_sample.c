/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sample.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:03:02 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/15 12:20:54 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/texture.h"

void	texture_free(t_texture *tex)
{
	if (!tex)
		return ;
	if (tex->data)
		free(tex->data);
	free(tex);
}

t_vec3	texture_sample(t_texture *tex, double u, double v)
{
	int				x;
	int				y;
	int				idx;
	unsigned char	*pixel;

	if (!tex || !tex->data)
		return (vec3_new(1, 0, 1));
	u = u - floor(u);
	v = v - floor(v);
	x = (int)(u * tex->width);
	y = (int)(v * tex->height);
	if (x >= tex->width)
		x = tex->width - 1;
	if (y >= tex->height)
		y = tex->height - 1;
	idx = (y * tex->width + x) * tex->channels;
	pixel = &tex->data[idx];
	return (vec3_new(pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0));
}
