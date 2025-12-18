/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/18 01:43:07 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

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

t_texture	*texture_load_ppm(const char *filename)
{
	t_texture	*tex;
	int			fd;
	char		c;
	char		magic[3];
	int			max_val;

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
	tex->channels = 3;
	tex->data = malloc(tex->width * tex->height * 3);
	if (!tex->data || max_val != 255)
		return (free(tex->data), free(tex), close(fd), NULL);
	if (read(fd, tex->data, tex->width * tex->height * 3)
		!= tex->width * tex->height * 3)
		return (free(tex->data), free(tex), close(fd), NULL);
	return (close(fd), tex);
}

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

void	sphere_get_uv(t_vec3 point, t_vec3 center, double *u, double *v)
{
	t_vec3	local;
	double	theta;
	double	phi;

	local = vec3_normalize(vec3_sub(point, center));
	theta = atan2(local.x, local.z);
	phi = asin(local.y);
	*u = 1.0 - (theta + M_PI) / (2.0 * M_PI);
	*v = (phi + M_PI / 2.0) / M_PI;
}

t_vec3	apply_texture(t_hit *hit)
{
	if (!hit->texture)
		return (hit->color);
	return (texture_sample(hit->texture, hit->u, hit->v));
}

t_vec3	apply_bump_map(t_hit *hit)
{
	t_vec3	color_c;
	t_vec3	color_u;
	t_vec3	color_v;
	double	du;
	double	dv;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	perturbed;
	double	delta;

	if (!hit->bump_map)
		return (hit->normal);
	delta = 0.001;
	color_c = texture_sample(hit->bump_map, hit->u, hit->v);
	color_u = texture_sample(hit->bump_map, hit->u + delta, hit->v);
	color_v = texture_sample(hit->bump_map, hit->u, hit->v + delta);
	du = (color_u.x + color_u.y + color_u.z) / 3.0
		- (color_c.x + color_c.y + color_c.z) / 3.0;
	dv = (color_v.x + color_v.y + color_v.z) / 3.0
		- (color_c.x + color_c.y + color_c.z) / 3.0;
	tangent = vec3_normalize(vec3_cross(hit->normal, vec3_new(0, 1, 0)));
	if (vec3_length(tangent) < EPSILON)
		tangent = vec3_normalize(vec3_cross(hit->normal, vec3_new(1, 0, 0)));
	bitangent = vec3_cross(hit->normal, tangent);
	perturbed = vec3_add(hit->normal, vec3_scale(tangent, -du * BUMP_STRENGTH * 10.0));
	perturbed = vec3_add(perturbed, vec3_scale(bitangent, -dv * BUMP_STRENGTH * 10.0));
	return (vec3_normalize(perturbed));
}
