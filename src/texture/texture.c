/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/23 03:22:51 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/texture.h"
#include "../../includes/hit.h"

static void	skip_whitespace_comments(int fd, char *c)
{
	while (*c == ' ' || *c == '\t' || *c == '\n' || *c == '\r' || *c == '#')
	{
		if (*c == '#')
		{
			while (*c != '\n' && read(fd, c, 1) == 1)
				;
		}
		if (read(fd, c, 1) != 1)
			break ;
	}
}

static int	read_ppm_int(int fd, char *c)
{
	int	value;

	skip_whitespace_comments(fd, c);
	value = 0;
	while (*c >= '0' && *c <= '9')
	{
		value = value * 10 + (*c - '0');
		if (read(fd, c, 1) != 1)
			break ;
	}
	return (value);
}

static int	read_ppm_data(t_texture *tex, int fd, int max_val)
{
	int	data_size;

	tex->channels = 3;
	data_size = tex->width * tex->height * 3;
	tex->data = malloc(data_size);
	if (!tex->data || max_val != 255)
		return (free(tex->data), free(tex), close(fd), 0);
	if (read(fd, tex->data, data_size) != data_size)
		return (free(tex->data), free(tex), close(fd), 0);
	return (1);
}

t_texture	*texture_load_ppm(const char *filename)
{
	t_texture	*tex;
	int			fd;
	char		c;
	char		magic[3];
	int			max_val;

	printf("\033[32mLoading texture: \033[1;32m%s\033[0m\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (read(fd, magic, 2) != 2 || magic[0] != 'P' || magic[1] != '6')
		return (close(fd), NULL);
	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (close(fd), NULL);
	read(fd, &c, 1);
	tex->width = read_ppm_int(fd, &c);
	tex->height = read_ppm_int(fd, &c);
	max_val = read_ppm_int(fd, &c);
	if (!read_ppm_data(tex, fd, max_val))
		return (NULL);
	return (close(fd), tex);
}
