/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:54:21 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/04 14:50:34 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "parser_internal.h"
#include "stdbool.h"
//TO DO: IMPORTANTE este parseo todavia es primitivo detecta el caso de que los elemento que se deberian mandar estuvieran incorrectos pero 
//si por ejemplo en en la linea que contien la informacion de ambient light contiene el ratio correcto y la escala rgb correcto pero luego en esa misma linea 
//ponen cualquier otra cosa no lo detecta es mas o menos facil de hacer pero no se puede olvidar dicho esto que la luz en general y los objetos


//comprueba unicamente si existe y si termina en .rt
void parser_file_name(char *file)
{
   int fd_tester;

    if(ft_strncmp(file + ft_sstrlen(file) - 2 , ".rt", 2) != 0)
        error_manager("file extension isn't .rt please correct");
    fd_tester = open(file, O_RDONLY);
    if(fd_tester < 0)
        error_manager("invalid file please check if it exits");
}
//comprueba si el valor dado esta en el rango avalidado con float para abarcar todos los casos
bool if_betwen_values(float element_to_check, float minmun_value , float maximun_value)
{
    if(element_to_check > maximun_value || element_to_check < minmun_value)
        return(false);
    return(true);
}
//primero comprueba si ya existe un element para esa lista la cual tiene que estar conformada por solo uno  en cuyo caso imprime error y
// destruye la lista luego comprobara el elemento del char *y lo pasarar por un chequer especifico para los elementos si es valido sigue 
//añadiendo elementos a las listas si no coje imprime mensaje de error y libera la lista
void ambient_light_parser(char **actual_element, t_list **list_to_add_element)
{
    int i;
    int j;
    char **rgb_to_split;
    t_list **rgb_list;
    float *actual_float;
    
    
    i = 1;
    if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) == 0 && *list_to_add_element) 
        ft_printf("%s\n","multiple ambient light declaration detected please check");
    else if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) != 0 )
        return ;
    rgb_list = ft_calloc(1, sizeof(t_list *));    
    while(actual_element[1][i])
    {
        if(ft_isdigit(actual_element[1][i]) == 0 && actual_element[1][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in ambient light ratio");
            free(list_to_add_element);
            return ;
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float)); 
    *actual_float = ft_float(actual_element[1]);
     if(if_betwen_values(*actual_float, 0,  1) == false);
            ft_printf("%s\n","no valid parametter find in ambient light ratio");
    ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
    rgb_to_split = ft_split(actual_element[2], ',');
    while(rgb_to_split[j])
    {
        while(rgb_to_split[j][i])
        { 
        if(ft_isdigit(rgb_to_split[j][i]) == 0)
        {
            ft_printf("%s\n","no valid parametter find in ambient light rgb");
            free(list_to_add_element);
            return ;
        }
        i++;
        }
         *actual_float = ft_float(rgb_to_split[j]); 
         if(if_betwen_values(*actual_float, 0, 250) == false);
            ft_printf("%s\n","no valid parametter find in ambient light rgb");
        ft_lstadd_back(rgb_list, ft_lstnew(actual_float));
        j++;
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(rgb_list));
}
//TO DO: hay que crear otra lista enlazada la cual servira como en content de la actual esto esta hecho asi para luego facilitar la conversion a la estructura final
void light_parser(char **actual_element, t_list **list_to_add_element)
{
    
}
//funcion general para todos los parser el cual devera recibir 2 parametros una lista con la informacion 2 la funcion que parsea ese elemento en concreto esta  recibira 2 a su vez uno por el char** 
//y otro por la lista resultatnte para poder asignar varios elementos como los objetos y para evitar duplicados de la iluminacion ambietal por ejemplo
t_list **general_parser(t_list    **list__to_track, void f(void *,void *))
{
    t_list **result;
    t_list *actual_node;

    if(!list__to_track || *list__to_track == NULL)
        return(NULL);
    result = ft_calloc(1, sizeof(t_list *));
    actual_node = *list__to_track;
    while(actual_node)
    {
        f(actual_node->content, result);
        if(!result)
            return(NULL);
        actual_node = actual_node->next;
    }
    return(result);
    
}
//primero comprueba si ya existe un element para esa lista la cual tiene que estar conformada por solo uno  en cuyo caso imprime error y
// destruye la lista luego comprobara el elemento del char *y lo pasarar por un chequer especifico para los elementos si es valido sigue 
//añadiendo elementos a las listas si no coje imprime mensaje de error y libera la lista en este caso dentro de lista se encuentra el puntero a 2 listas
// mas una siendo para el vector y otra para la posicion xyz
void camera_parser(char **actual_element, t_list **list_to_add_element)
{ 
    int i;
    int j;
    char **x_y_z_to_split;
    t_list **xyz_list;
    float *actual_float;
    
    
    i = 0;
    j = 0;
    if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) == 0 && *list_to_add_element) 
        ft_printf("%s\n","multiple Camaera declaration detected please check");
    else if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) != 0 )
        return ;
    xyz_list = ft_calloc(1, sizeof(t_list *));
    x_y_z_to_split = ft_split(actual_element[1], ',');
     while(x_y_z_to_split[j])
    {
        if(x_y_z_to_split[j][i] == '-')
            i++;
        while(x_y_z_to_split[j][i])
        { 
        if(ft_isdigit(x_y_z_to_split[j][i]) == 0 && x_y_z_to_split[j][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in camera position rgb");
            free(list_to_add_element);
            return ;
        }
        i++;
        }
         *actual_float = ft_float(x_y_z_to_split[j]);
        ft_lstadd_back(xyz_list, ft_lstnew(actual_float));
        j++;
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(xyz_list));
    i = 0;
    xyz_list = ft_calloc(1, sizeof(t_list *));
    x_y_z_to_split = ft_split(actual_element[2], ',');
    while(x_y_z_to_split[j])
    {
        if(x_y_z_to_split[j][i] == '-')
            i++;
        while(x_y_z_to_split[j][i])
        { 
        if(ft_isdigit(x_y_z_to_split[j][i]) == 0 && x_y_z_to_split[j][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in camera  vector rgb");
            free(list_to_add_element);
            return ;
        }
        i++;
        }
         *actual_float = ft_float(x_y_z_to_split[j]);
        if(if_betwen_values(*actual_float, -1, 1) == false);
            ft_printf("%s\n","no valid parametter find in camera vector");
        ft_lstadd_back(xyz_list, ft_lstnew(actual_float));
        j++;
    
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(xyz_list));
    i = 0;
    while(actual_element[3][i])
    {
        if(ft_isdigit(actual_element[1][i]) == 0 && actual_element[1][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in ambient light ratio");
            free(list_to_add_element);
            return ;
        }
        i++;
    }
        *actual_float = ft_float(x_y_z_to_split[j]);
        if(if_betwen_values(*actual_float, 0, 180) == false);
            ft_printf("%s\n","no valid parametter find in camera vector");
        ft_lstadd_back(xyz_list, ft_lstnew(actual_float));
}

//asignar la structura primitiva de la escena separada en en listas simples sin ninguna estructura para ser asignadas a poseriori
static  int    primitive_escene_t_asignation(t_list **element_to_conver, primitive_escene_t *struct_to_assignate)
{
    struct_to_assignate->al = general_parser(element_to_conver, ambient_light_parser);
    if(!struct_to_assignate->al)
        return(-1);
    struct_to_assignate->camera = general_parser(element_to_conver, camera_parser);
    if(!struct_to_assignate->camera)
        return(-1);
        
} 
//separalas lineas del archivo.rt en char** spliteados por espacio y separado en los diferentes elementos 
static  t_list **get_file_content(char *file)
{
    int fd;
    t_list **result;
    char line_to_do_split;
    char **axu_line;
    result = ft_calloc(1, sizeof(t_list *));
    if(!result)
        return(NULL);
    fd = open(file, O_RDONLY);
    if(fd < 0)
        return(NULL);
    line_to_do_split = get_next_line(fd);
    while(line_to_do_split != NULL)
    {
        axu_line = ft_split(line_to_do_split, ' ');
        free(line_to_do_split);
        ft_lstadd_back(result, ft_lstnew(axu_line));
        line_to_do_split = get_next_line(fd);
    }
    close(fd);
    return(result);
    
}
//returna una structura la cual solo contiene valores valido sino return a nulo a paratir de esta se contruira la siguiente ewstructura la cual dependera de los demas modulos"luz, camara, obejects, etc)
primitive_escene_t *escene_primiteve_contructor(char *file)
{
    primitive_escene_t *result;
    char **file_content;
    
    parser_file_name(file);
    result = ft_calloc(1, sizeof(primitive_escene_t));
    if(primitive_escene_t_asignation(get_file_content(file), z))
    
    
    
}
