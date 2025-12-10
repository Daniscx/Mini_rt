/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:54:21 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/10 20:21:07 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TO DO: manejar leaks y    el mandar bien los mensajes de error lo demas ya esta cubierto separa en funciones pero eso ya es cosa de la norma
#include "math.h"
#include "parser_internal.h"
#include "stdbool.h"
#include "../../includes/mini_rt.h"

static size_t double_array_len(char **doble);
static bool correct_number_of_elements(char **element);
//comprueba unicamente si existe y si termina en .rt
void parser_file_name(char *file)
{
   int fd_tester;

    if(ft_strncmp(file + ft_sstrlen(file) - 3 , ".rt", 3) != 0)
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
//funcion generica para crear una lista en la cual se guardaran los argumentos con multpiles elemento por ejemplo las cordenadas de un objeto ,vector ,el rgb, a parte de esto
//incluye una opcion, para hacer checkeo de valores maximos , si se manda a los argumentos max y min ambos como 0 no entra en el if esto ocurre casi esclusivamente 
//con el caso de las cordenadas todos los demas incluyen hasta cierto punto.
t_list **list_of_float_checker(char **splited_element, float max  , float min, bool range)
{
    t_list **resuslt;
    int i;
    int j;
    float *actual_float;
    
    j = 0; 
    i = 0;
    resuslt = ft_calloc(1, sizeof(t_list *));
    while(splited_element[j])
    {
        if(splited_element[j][i] == '-')
            i++;
        while(splited_element[j][i])
        { 
            if(ft_isdigit(splited_element[j][i]) == 0)
            {
                ft_printf("%s","no valid parametter find in :");
                return(NULL);
            }
            i++;
        }
        i = 0;
        actual_float = ft_calloc(1, sizeof(float));
         *actual_float = ft_float(splited_element[j]); 
         if(if_betwen_values(*actual_float, min, max) == false && range == true)
         {
            ft_printf("%s\n","no valid value for thwe mayority");
            printf("%f\n", *actual_float);
            return(NULL);
            
         }
            
        ft_lstadd_back(resuslt, ft_lstnew(actual_float));
        j++;
    }
    return(resuslt);
}
//primero comprueba si ya existe un element para esa lista la cual tiene que estar conformada por solo uno  en cuyo caso imprime error y
// destruye la lista luego comprobara el elemento del char *y lo pasarar por un chequer especifico para los elementos si es valido sigue 
//añadiendo elementos a las listas si no coje imprime mensaje de error y libera la lista
void ambient_light_parser(char **actual_element, t_list **list_to_add_element)
{
    int i;
    char **rgb_to_split;
    float *actual_float;
    
    
    i = 1;
    if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) == 0 && *list_to_add_element) 
        ft_printf("%s\n","multiple ambient light declaration detected please check");
    else if(ft_strncmp(actual_element[0],"A", ft_strlen(actual_element[0])) != 0 )
        return ; 
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
     if(if_betwen_values(*actual_float, 0,  1) == false)
            ft_printf("%s\n","no valid parametter find in ambient light ratio");
    ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
    rgb_to_split = ft_split(actual_element[2], ',');
    
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_of_float_checker(rgb_to_split, 255 , 0, true)));
}
//TO DO: hay que crear otra lista enlazada la cual servira como en content de la actual esto esta hecho asi para luego facilitar la conversion a la estructura final
void light_parser(char **actual_element, t_list **list_to_add_element)
{
    t_list **new_light_element;
    char **splited_element;
    int i;
    float *actual_float;
    
    i = 0;
    
    if(ft_strncmp(actual_element[0], "L", ft_strlen(actual_element[1])))
        return ;
    new_light_element = ft_calloc(1,sizeof(t_list *));
    splited_element = ft_split(actual_element[1], ',');
    if(!splited_element || *splited_element == NULL)
        return;
    ft_lstadd_front(new_light_element, ft_lstnew(list_of_float_checker(splited_element, 0, 0, false)));
    while(actual_element[2][i])
    {
        if(ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in light ratio");
            free(list_to_add_element);
            return ;
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_float(actual_element[2]);
    ft_lstadd_back(new_light_element, ft_lstnew(actual_float));
    splited_element = ft_split(actual_element[3], ',');
    if(!splited_element || *splited_element == NULL)
        return(free(list_to_add_element));
    ft_lstadd_back(new_light_element, ft_lstnew(list_of_float_checker(splited_element, 255 , 0, true)));
    ft_lstadd_back(list_to_add_element, ft_lstnew(new_light_element));
    
}
//funcion general para todos los parser el cual devera recibir 2 parametros una lista con la informacion 2 la funcion que parsea ese elemento en concreto esta  recibira 2 a su vez uno por el char** 
//y otro por la lista resultatnte para poder asignar varios elementos como los objetos y para evitar duplicados de la iluminacion ambietal por ejemplo
t_list **general_parser(t_list    **list__to_track, void f(char **,t_list **))
{
    t_list **result;
    t_list *actual_node;

    if(!list__to_track || *list__to_track == NULL)
        return(NULL);
    result = ft_calloc(1, sizeof(t_list *));
    actual_node = *list__to_track;
    while(actual_node)
    {
        if(correct_number_of_elements(actual_node->content) == false)
            return(free(result), NULL);
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
    char **x_y_z_to_split;
    float *actual_float;
    t_list **list_float;
    
    
    i = 0;
    if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) == 0 && *list_to_add_element) 
        ft_printf("%s\n","multiple Camaera declaration detected please check");
    else if(ft_strncmp(actual_element[0],"C", ft_strlen(actual_element[0])) != 0 )
        return ;
    x_y_z_to_split = ft_split(actual_element[1], ',');
    list_float = list_of_float_checker(x_y_z_to_split, 0 , 0, false);
    if(!list_float)
    {
        ft_printf("%s\n", "camera_element");
        return(free(list_to_add_element));
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    x_y_z_to_split = ft_split(actual_element[2], ',');
    list_float = list_of_float_checker(x_y_z_to_split, 0 , 0, false);
    if(!list_float)
    {
        ft_printf("%s\n", "camera_element");
        return(free(list_to_add_element));
    }
    ft_lstadd_back(list_to_add_element, ft_lstnew(list_float));
    i = 0;
    if(actual_element[3][i] == '-')
        i++;
    while(actual_element[3][i])
    {
        if(ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in ambient light ratio");
            free(list_to_add_element);
            return ;
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float *));
    *actual_float = ft_float(actual_element[3]);
    if(if_betwen_values(*actual_float, 0, 180) == false)
        ft_printf("%s\n","no valid parametter find in camera vector");
    ft_lstadd_back(list_to_add_element, ft_lstnew(actual_float));
}
//el parser de la esfera  primero el centro de la esfera en las coordenadas x y z luego el diametro de la esfera y finalmente el rgb
static t_list **sphere_parser(char **actual_element)
{
    t_list **result;
    t_list **float_list;
    char **element_splited;
    int i;
    float   *actual_float;

    
    
    result = ft_calloc(1, sizeof(t_list *));
    ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
    element_splited = ft_split(actual_element[1], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false);
    free_double_pointer(element_splited);
     if(!float_list)
    {
        ft_printf("%s\n", "sphere element");
        return(free(result),NULL);
    }
     ft_lstadd_back(result, ft_lstnew(float_list));
     i = 0;
     if(actual_element[2][i] == '-')
            i++;
     while(actual_element[2][i])
    {
        if(ft_isdigit(actual_element[2][i]) == 0 && actual_element[2][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in sphere diametre");
            free(result);
            return (NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_float(actual_element[2]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    element_splited = ft_split(actual_element[3], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true);
    free_double_pointer(element_splited);
    if(!float_list)
    {
        ft_printf("%s\n", "sphere element");
        return(free(result),NULL);
    }
       
    return(result);
}
/*bool is_a_element(char *indetificator)
{
    size_t len;
    len = ft_strlen(indetificator);
    if(ft_strncmp(indetificator, "A", len) == 0 ||ft_strncmp(indetificator, "C", len) == 0|| 
        ft_strncmp(indetificator, "L", len) == 0 || ft_strncmp(indetificator, "cy", len) == 0 || 
        ft_strncmp(indetificator, "pl", len) == 0 || ft_strncmp(indetificator, "sp", len) == 0)
            return(true);
    return(false);
}*/
int	ft_ispace(char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}
bool str_empty(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(ft_ispace(str[i]) == 0)
                return(false);
        i++;
    }
    return(true);
}
static bool correct_number_of_elements(char **element)
{
    size_t nb_of_args;
    size_t len;
    len = ft_strlen(element[0]);
    nb_of_args = double_array_len(element + 1);
    
    if( ft_strncmp(element[0], "C", len) == 0||  ft_strncmp(element[0], "L", len) == 0 || 
        ft_strncmp(element[0], "pl", len) == 0 || ft_strncmp(element[0], "sp", len) == 0)
    {
        if(nb_of_args == 3)
            return(true);
        else
            return(false);
    }
    else if(ft_strncmp(element[0], "A", len) == 0 && nb_of_args == 2)
        return(true);
    else if (ft_strncmp(element[0], "cy", len) == 0 && nb_of_args ==  5)
        return(true);
    else
    {
        ft_printf("%s", "the file .rt contain incorrect elements ,please correct them");
         return(false);
    }
       
}
static  size_t double_array_len(char **doble)
{
    size_t j;
    j = 0;
    while(doble[j])
     j++;
    return(j);
}
//parseo especifico del cilindro primero comprueba las cordenadas luego el vector director luego el diametro , luego la altura y finalmente el color rgb misma forma 
//como la que  se trabaja en los demas 
static t_list **cylindrer_parser(char **actual_element)
{
    t_list **result;
    t_list **float_list;
    char **element_splited;
    int i;
    float   *actual_float;
    
    result = ft_calloc(1, sizeof(t_list *));
    ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
    printf("%s ", "llega aqui");
    element_splited = ft_split(actual_element[1], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false);
    free_double_pointer(element_splited);
    if(!float_list)
        return(free(result),NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[2], ',');
    float_list = list_of_float_checker(element_splited, 1, -1, true);
    free_double_pointer(element_splited);
    if(!float_list)
        return(free(result),NULL);
     ft_lstadd_back(result, ft_lstnew(float_list));
    i = 0;
    if(actual_element[3][i] == '-')
        i++;
    while(actual_element[3][i])
    {
        if(ft_isdigit(actual_element[3][i]) == 0 && actual_element[3][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in cylindrer diametre");
            free(result);
            return (NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_float(actual_element[3]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    i = 0;
    if(actual_element[4][i] == '-')
        i++;
     while(actual_element[4][i])
    {
        if(ft_isdigit(actual_element[4][i]) == 0 && actual_element[4][i] != '.')
        {
            ft_printf("%s\n","no valid parametter find in cylindrer hight");
            free(result);
            return (NULL);
        }
        i++;
    }
    actual_float = ft_calloc(1, sizeof(float));
    *actual_float = ft_float(actual_element[2]);
    ft_lstadd_back(result, ft_lstnew(actual_float));
    element_splited = ft_split(actual_element[5], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true);
    free_double_pointer(element_splited);
    if(!float_list)
        return(free(result),NULL);
    ft_lstadd_back(result, ft_lstnew(float_list));
    return(result);
}
//parser del plano primero se parsea las cordenadas de un punto del plano luego el vector normal "el que es perpendicular al plano" y finalmente en rgb
static t_list **plane_parser(char **actual_element)
{
    t_list **result;
    t_list **float_list;
    char **element_splited;
        
    result = ft_calloc(1, sizeof(t_list *));
    ft_lstadd_back(result, ft_lstnew(ft_strdup(actual_element[0])));
    element_splited = ft_split(actual_element[1], ',');
    float_list = list_of_float_checker(element_splited, 0, 0, false);
    free_double_pointer(element_splited);
     if(!float_list)
    {
        ft_printf("%s\n", "plane element");
        return(free(result),NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[2], ',');
    float_list = list_of_float_checker(element_splited, 1, -1, true);
    free_double_pointer(element_splited);
      if(!float_list)
    {
        ft_printf("%s\n", "plane element");
        return(free(result),NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    element_splited = ft_split(actual_element[3], ',');
    float_list = list_of_float_checker(element_splited, 255, 0, true);
    free_double_pointer(element_splited);
      if(!float_list)
    {
        ft_printf("%s\n", "plane element");
        return(free(result),NULL);
    }
    ft_lstadd_back(result, ft_lstnew(float_list));
    return(result);
}

static void object_parser(char **actual_element, t_list **list_to_add_element)
{
    size_t len;
    t_list **result;
    

    len = ft_strlen(actual_element[1]);
    if(ft_strncmp(actual_element[1], "sp", len) == 0)
    {
        result = sphere_parser(actual_element);
        if(!result)
            return(free(list_to_add_element));
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
        if(ft_strncmp(actual_element[1], "pl", len) == 0)
    {
        result = plane_parser(actual_element);
        if(!result)
            return(free(list_to_add_element));
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
        if(ft_strncmp(actual_element[1], "cy", len) == 0)
    {
        result = cylindrer_parser(actual_element);
        if(!result)
            return(free(list_to_add_element));
        ft_lstadd_back(list_to_add_element, ft_lstnew(result));
    }
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
    struct_to_assignate->light = general_parser(element_to_conver, light_parser);
    if(!struct_to_assignate->light)
        return(-1);
     struct_to_assignate->object = general_parser(element_to_conver, object_parser);
    if(!struct_to_assignate->object)
        return(-1);
    return(0);
        
} 
//separalas lineas del archivo.rt en char** spliteados por espacio y separado en los diferentes elementos 
static  t_list **get_file_content(char *file)
{
    int fd;
    t_list **result;
    char *line_to_do_split;
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
        if(ft_strchr(line_to_do_split, '\n'))
            line_to_do_split = ft_substr(line_to_do_split, 0, ft_strlen(line_to_do_split) - 1);
        if(str_empty(line_to_do_split) == true)
            {
                free(line_to_do_split);
                line_to_do_split = get_next_line(fd);
                continue;
            }
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
    
    parser_file_name(file);
    result = ft_calloc(1, sizeof(primitive_escene_t));
    if(primitive_escene_t_asignation(get_file_content(file), result) == -1)
        return(NULL);
    print_primitive_escene(result);
    return(result);    
}
