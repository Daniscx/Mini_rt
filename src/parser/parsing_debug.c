/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:30:30 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/24 01:15:21 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"

void	print_light(t_list **light)
{
	t_list	*aux;
	t_list	*sub;

	printf("%s\n", "LIGHT:");
	aux = *light;
	sub = *(t_list **)aux->content;
	while (sub)
	{
		printf("%f\n", *(float *)sub->content);
		sub = sub->next;
	}
	aux = aux->next;
	printf("%f\n", *(float *)aux->content);
	aux = aux->next;
	sub = *(t_list **)aux->content;
	while (sub)
	{
		printf("%f\n", *(float *)sub->content);
		sub = sub->next;
	}
}

void	print_plane(t_list **plane)
{
	t_list	*aux;
	t_list	*sub;

	printf("%s\n", "plane:");
	aux = *plane;
	aux = aux->next;
	while (aux)
	{
		sub = *(t_list **)aux->content;
		while (sub)
		{
			printf("%f\n", *(float *)sub->content);
			sub = sub->next;
		}
		aux = aux->next;
	}
}

void	print_sphere(t_list **object)
{
	t_list	*aux;
	t_list	*sub;

	printf("%s\n", "sphere:");
	aux = *object;
	aux = aux->next;
	sub = *(t_list **)aux->content;
	while (sub)
	{
		printf("%f\n", *(float *)sub->content);
		sub = sub->next;
	}
	aux = aux->next;
	printf("%f\n", *(float *)aux->content);
	aux = aux->next;
	sub = *(t_list **)aux->content;
	while (sub)
	{
		printf("%f\n", *(float *)sub->content);
		sub = sub->next;
	}
}

void	print_cameras(t_list **camera)
{
	t_list	*aux;
	t_list	*sub;

	printf("%s\n", "CAMERA:");
	aux = *camera;
	sub = *(t_list **)aux->content;
	while (sub)
	{
		printf("%f\n", *(float *)sub->content);
		sub = sub->next;
	}
	aux = aux->next;
	sub = *(t_list **)aux->content;
	while (sub)
	{
		printf("%f\n", *(float *)sub->content);
		sub = sub->next;
	}
	aux = aux->next;
	printf("%f\n", *(float *)aux->content);
}

void	print_primitive_escene(t_primitive_escene *escene)
{
	t_list	*aux;
	t_list	*sub;

	printf("%s\n", "AL:");
	aux = *escene->al;
	printf("%f\n", *(float *)aux->content);
	aux = aux->next;
	sub = *(t_list **)aux->content;
	while (sub)
	{
		printf("%f\n", *(float *)sub->content);
		sub = sub->next;
	}
	aux = *(t_list **)escene->light;
	while (aux)
	{
		print_light(aux->content);
		aux = aux->next;
	}
	print_cameras(escene->camera);
}
