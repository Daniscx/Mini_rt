/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2026/01/14 12:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"
#include "../../includes/minirt.h"

static int	parse_cam_fov(char **elem, t_list **list, int line, t_error_list *e)
{
	int		i;
	float	*fov;

	i = 0;
	if (elem[3][i] == '-')
		i++;
	while (elem[3][i] && (ft_isdigit(elem[3][i]) || elem[3][i] == '.'))
		i++;
	if (elem[3][i])
		return (error_list_add(e, line, "Invalid num.", "FOV"), -1);
	fov = ft_calloc(1, sizeof(float));
	*fov = ft_atof(elem[3]);
	if (if_betwen_values(*fov, 0, 180) == false)
		return (free(fov), error_list_add(e, line, "FOV 0-180.", "FOV"), -1);
	return (ft_lstadd_back(list, ft_lstnew(fov)), 0);
}

static int	parse_cam_vectors(char **elem, t_list **list, int line,
		t_error_list *e)
{
	char		**xyz;
	t_list		**list_float;
	t_float_ctx	ctx;

	xyz = ft_split(elem[1], ',');
	ctx = (t_float_ctx){0, 0, false, line, e, "pos"};
	list_float = list_of_float_checker(xyz, &ctx);
	free_double_pointer(xyz);
	if (!list_float)
		return (-1);
	ft_lstadd_back(list, ft_lstnew(list_float));
	xyz = ft_split(elem[2], ',');
	ctx = (t_float_ctx){0, 0, false, line, e, "orient"};
	list_float = list_of_float_checker(xyz, &ctx);
	free_double_pointer(xyz);
	if (!list_float)
		return (-1);
	ft_lstadd_back(list, ft_lstnew(list_float));
	return (0);
}

int	camera_parser(char **elem, t_list **list, int line, t_error_list *e)
{
	if (ft_strncmp(elem[0], "C", ft_strlen(elem[0])) == 0 && *list)
		return (error_list_add(e, line, "Multiple camera.", "C"), -1);
	else if (ft_strncmp(elem[0], "C", ft_strlen(elem[0])) != 0)
		return (0);
	if (parse_cam_vectors(elem, list, line, e) == -1)
		return (-1);
	return (parse_cam_fov(elem, list, line, e));
}
