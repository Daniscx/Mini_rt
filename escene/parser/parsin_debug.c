/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:30:30 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/22 01:33:17 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
//INICIO del debuger de primitive
void print_light(t_list **light)
{
    t_list *aux;
    t_list *sub;
    
    printf("%s\n", "LIGHT:");
    aux = *light;
    sub = *(t_list **)aux->content;
    
    while(sub)
    {
         printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
    aux = aux->next;
    printf("%f\n", *(float *)aux->content);
    aux = aux->next;
    sub = *(t_list **)aux->content;
    while(sub)
    {
         printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
    aux = aux->next;
     
     
}
void    print_plane(t_list **plane)
{
       t_list *aux;
    t_list *sub;
    
    printf("%s\n", "plane:");
    aux = *plane;
    aux = aux->next;
    while(aux)
    {
        sub = *(t_list **)aux->content;
        while(sub)
        {
            printf("%f\n", *(float *)sub->content);
            sub = sub->next;
        }
        aux = aux->next;
    }
}
void print_sphere(t_list **object)
{
    t_list *aux;
    t_list *sub;
    
    printf("%s\n", "sphere:");
    aux = *object;
    aux = aux->next;
    sub = *(t_list **)aux->content;
    while(sub)
    {
        printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
    aux = aux->next;
    printf("%f\n", *(float *)aux->content);
    aux = aux->next;
    sub = *(t_list **)aux->content;
    while(sub)
    {
        printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
  
}
void    print_hell(t_list **object)
{
    t_list *aux;
    t_list *sub;
    
    printf("%s\n", "cylindrer:");
    aux = *object;
    aux = aux->next;
    sub = *(t_list **)aux->content;
    while(sub)
    {
        printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
    aux = aux->next;
    sub = *(t_list **)aux->content;
    while(sub)
    {
        printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
    aux = aux->next;
    printf("%f\n", *(float *)aux->content);
    aux = aux->next;
    printf("%f\n", *(float *)aux->content);
    aux = aux->next;
    sub = *(t_list **)aux->content;
    while(sub)
    {
        printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
    
}
void    print_objects(t_list **objects)
{
    t_list *aux;
    t_list *sub;
    
    printf("%s\n", "OBJECTS:");
    aux = *objects;
    while(aux)
    {
        sub = *(t_list **)aux->content;
        if(ft_strncmp((char *)sub->content, "sp", 2) == 0)
            print_sphere(aux->content);
        if(ft_strncmp((char *)sub->content, "pl", 2) == 0)
            print_plane(aux->content);
        if(ft_strncmp((char *)sub->content, "cy", 2) == 0)
            print_hell(aux->content);
        aux = aux->next;
    }
        
    
}
void    print_cameras(t_list **camera)
{
    t_list *aux;
    t_list *sub;
    
    printf("%s\n", "CAMERA:");
    aux = *camera;
    sub = *(t_list **)aux->content;
    while(sub)
    {
         printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
    aux = aux->next;
    sub = *(t_list **)aux->content;
    while(sub)
    {
         printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
    aux = aux->next;
    printf("%f\n", *(float *)aux->content);   
    
}
void print_primitive_escene(t_primitive_escene *escene)
{
    t_list *aux;
    t_list *sub;
    printf("%s\n", "AL:");    
    aux = *escene->al;
    printf("%f\n", *(float *)aux->content);
    aux = aux->next;
    sub = *(t_list **)aux->content;
    while(sub)
    {
        printf("%f\n", *(float *)sub->content);
        sub = sub->next;
    }
    aux = *(t_list **)escene->light;
    while(aux)
    {
        print_light(aux->content);
        aux = aux->next;
    }
    print_cameras(escene->camera);
    print_objects(escene->object);
    
}
