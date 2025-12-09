/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:30:21 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	render_scene(t_minirt *rt)
{
	int		x;
	int		y;
	int		color;
	double	gradient;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			gradient = (double)y / HEIGHT;
			color = create_rgb((int)(135 * (1 - gradient) + 206 * gradient),
					(int)(206 * (1 - gradient) + 235 * gradient),
					(int)(235 * (1 - gradient) + 255 * gradient));
			put_pixel(&rt->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
}
