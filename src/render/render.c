/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/10 18:24:07 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Dibuja un píxel en la imagen en memoria
** Parámetros:
**   - img: imagen donde dibujar
**   - x, y: coordenadas del píxel
**   - color: color en formato ARGB (0x00RRGGBB)
** Funcionamiento:
**   - Calcula la posición en memoria: y * line_len + x * bytes_por_pixel
**   - Escribe el color directamente en memoria
**   - Valida que las coordenadas estén dentro de la ventana
** Ventaja: Más rápido que mlx_pixel_put (no requiere X11 calls)
*/
static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
** Crea un color en formato ARGB a partir de componentes RGB
** Parámetros:
**   - r, g, b: componentes rojo, verde, azul [0-255]
** Retorna:
**   - Color en formato 0x00RRGGBB
** Funcionamiento:
**   - R << 16: coloca el rojo en los bits 16-23
**   - G << 8:  coloca el verde en los bits 8-15
**   - B:       coloca el azul en los bits 0-7
** Ejemplo: create_rgb(255, 0, 0) = 0x00FF0000 (rojo)
*/
static int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/*
** Renderiza la escena completa (actualmente solo gradiente de prueba)
** Parámetros:
**   - rt: estructura principal con imagen y escena
** Funcionamiento actual:
**   - Recorre cada píxel de la ventana
**   - Crea un gradiente vertical azul claro (cielo)
**   - Dibuja el píxel en la imagen en memoria
**   - Muestra la imagen en la ventana con mlx_put_image_to_window
** TODO: Implementar raytracing real:
**   - Generar rayo desde cámara para cada píxel
**   - Calcular intersecciones con objetos de la escena
**   - Aplicar iluminación y calcular color final
*/
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
