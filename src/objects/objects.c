/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:25:50 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:18:38 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"

static t_object	*object_costructor(t_list **components);

static enum e_objects	get_identificator(char *name)
{
	if (ft_strncmp(name, "cy", 2) == 0)
		return (Cy);
	else if (ft_strncmp(name, "spt", 3) == 0)
		return (Spt);
	else if (ft_strncmp(name, "plc", 3) == 0)
		return (Plc);
	else if (ft_strncmp(name, "pl", 2) == 0)
		return (Pl);
	else if (ft_strncmp(name, "sp", 2) == 0)
		return (Sp);
	else if (ft_strncmp(name, "co", 2) == 0)
		return (Co);
	else
		return (NONE_MANAGE);
}

static void	*object_create(enum e_objects id, t_list **obj, t_object *st)
{
	if (id == Cy)
		return (cylinder_constructor(obj, st));
	else if (id == Sp)
		return (sphere_constructor(obj, st, false));
	else if (id == Pl)
		return (plane_constructor(obj, st, false));
	else if (id == Co)
		return (cone_constructor(obj, st));
	else if (id == Plc)
		return (plane_constructor(obj, st, true));
	else if (id == Spt)
		return (sphere_constructor(obj, st, true));
	return (NULL);
}

static t_object	*object_costructor(t_list **components)
{
	t_object	*result;
	t_list		*aux;

	if (!components || !*components)
		return (NULL);
	result = ft_calloc(1, sizeof(t_object));
	aux = *components;
	if (!aux || !aux->content)
		return (result);
	result->identificator = get_identificator((char *)aux->content);
	aux = aux->next;
	result->figure = object_create(result->identificator, &aux, result);
	return (result);
}

t_list	**object_list_constructor(t_list **components)
{
	t_list		*aux;
	t_list		**result;
	t_object	*obj;

	result = ft_calloc(1, sizeof(t_list *));
	if (!components || !*components)
		return (result);
	aux = *components;
	while (aux)
	{
		obj = object_costructor((t_list **)aux->content);
		if (obj)
			ft_lstadd_back(result, ft_lstnew(obj));
		aux = aux->next;
	}
	return (result);
}
