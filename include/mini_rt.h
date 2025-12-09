/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:31:11 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:31:12 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define WIDTH 800
# define HEIGHT 600
# define WIN_TITLE "miniRT"

# define ESC_KEY 65307

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_img
{
	void			*img_ptr;
	char			*pixels_ptr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_camera
{
	t_vec3			position;
	t_vec3			direction;
	t_vec3			right;
	t_vec3			up;
	double			fov;
	double			aspect_ratio;
}					t_camera;

typedef struct s_escene
{
	t_list			**object;
	t_list			**light;
	void			*al;
	void			*camera;
}					escene_t;

typedef struct s_parse_primitive
{
	t_list			**object;
	t_list			**light;
	t_list			**al;
	t_list			**camera;
}					parse_primitive_t;

typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_camera		camera;
	escene_t		*scene;
}					t_minirt;

void				error_manager(char *error_message);

void				minirt_init(t_minirt *rt);
void				minirt_cleanup(t_minirt *rt);

int					close_handler(t_minirt *rt);
int					key_handler(int keycode, t_minirt *rt);

void				camera_init(t_camera *camera);
void				camera_move(t_camera *camera, t_vec3 offset);
void				camera_rotate(t_camera *camera, double yaw, double pitch);

void				render_scene(t_minirt *rt);

t_vec3				vec3_new(double x, double y, double z);
t_vec3				vec3_add(t_vec3 a, t_vec3 b);
t_vec3				vec3_sub(t_vec3 a, t_vec3 b);
t_vec3				vec3_scale(t_vec3 v, double scalar);
double				vec3_dot(t_vec3 a, t_vec3 b);
t_vec3				vec3_cross(t_vec3 a, t_vec3 b);
t_vec3				vec3_normalize(t_vec3 v);
double				vec3_length(t_vec3 v);

escene_t			*escene_constructor(char *file);
void				escene_destructor(escene_t *escene);

parse_primitive_t	*parse_primiteve_contructor(char *file);
void				*parse_primiteve_destructor(parse_primitive_t *parse);

void				parser_file_name(char *file);
bool				if_betwen_values(float element_to_check, float minmun_value,
						float maximun_value);
void				ambient_light_parser(char **actual_element,
						t_list **list_to_add_element);
void				light_parser(char **actual_element,
						t_list **list_to_add_element);
t_list				**general_parser(t_list **list__to_track,
						void f(void *, void *));
void				camera_parser(char **actual_element,
						t_list **list_to_add_element);

t_list				*ft_lstnew(void *content);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_itoa(int n);
void				ft_putendl_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_printf(char const *str, ...);
int					ft_putchar(int pf);
int					ft_putstr(char *str);
int					ft_putnb(int pf);
int					ft_puthexnum(unsigned int pf);
int					ft_puthexnumax(unsigned int pf);
int					ft_putunmath(unsigned int pf);
int					ft_putpointer(void *pf);
int					ft_selector(va_list pf, char const *str);
char				*get_next_line(int fd);
char				*ft_sstrchr(char *s, int j);
void				*ft_caalloc(size_t nmbr, size_t sz);
char				*ft_sstrjoin(char *fv, char *s);
int					ft_sstrlen(char *ret);
long long			ft_atol(const char *nptr);
void				free_double_pointer(char **dbpt);
float				ft_float(char *number);

#endif