/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/24 01:14:39 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minirt.h"

static void	write_bmp_headers(int fd, int width, int height)
{
	unsigned char	header[54];
	int				file_size;
	int				pad;

	pad = (4 - (width * 3) % 4) % 4;
	file_size = 54 + (width * 3 + pad) * height;
	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	*(int *)(header + 2) = file_size;
	*(int *)(header + 10) = 54;
	*(int *)(header + 14) = 40;
	*(int *)(header + 18) = width;
	*(int *)(header + 22) = height;
	*(short *)(header + 26) = 1;
	*(short *)(header + 28) = 24;
	write(fd, header, 54);
}

static void	write_bmp_row(int fd, t_img *img, int y)
{
	int				x;
	int				pad;
	unsigned char	pixel[3];
	unsigned int	color;

	pad = (4 - (img->width * 3) % 4) % 4;
	x = -1;
	while (++x < img->width)
	{
		color = *(unsigned int *)(img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8)));
		pixel[0] = color & 0xFF;
		pixel[1] = (color >> 8) & 0xFF;
		pixel[2] = (color >> 16) & 0xFF;
		write(fd, pixel, 3);
	}
	write(fd, "\0\0\0", pad);
}

static void	write_bmp_pixels(int fd, t_img *img)
{
	int	y;

	y = img->height;
	while (--y >= 0)
		write_bmp_row(fd, img, y);
}

void	generate_filename(char *filename)
{
	time_t	now;
	int		i;

	now = time(NULL);
	ft_strlcpy(filename, SCREENSHOT_DIR "/screenshot_", 256);
	i = ft_strlen(filename);
	filename[i++] = '0' + ((now / 100000) % 10);
	filename[i++] = '0' + ((now / 10000) % 10);
	filename[i++] = '0' + ((now / 1000) % 10);
	filename[i++] = '0' + ((now / 100) % 10);
	filename[i++] = '0' + ((now / 10) % 10);
	filename[i++] = '0' + (now % 10);
	ft_strlcpy(filename + i, ".bmp", 256 - i);
}

int	save_bmp(t_img *img, char *filename)
{
	int	fd;

	mkdir(SCREENSHOT_DIR, 0755);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	write_bmp_headers(fd, img->width, img->height);
	write_bmp_pixels(fd, img);
	close(fd);
	return (1);
}
