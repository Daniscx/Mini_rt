/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:13:33 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/20 03:33:16 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <string.h>
# include <time.h>
# include <sys/stat.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

/* =[ List Structure ]====================================================== */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* =[ Part I ]============================================================== */

size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little, size_t len);
char				*ft_strdup(const char *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *nptr);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);

/* =[ Part II ]============================================================= */

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/* =[ libft List ]========================================================== */

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);

/* =[ Get Next Line ]======================================================= */

char				*get_next_line(int fd);
char				*ft_sstrchr(char *s, int j);
void				*ft_caalloc(size_t nmbr, size_t sz);
char				*ft_sstrjoin(char *fv, char *s);
int					ft_sstrlen(char *ret);

/* =[ Printf ]============================================================== */

int					ft_printf(char const *str, ...);
int					ft_putchar(int pf);
int					ft_putstr(char *str);
int					ft_putnb(int pf);
int					ft_puthexnum(unsigned int pf);
int					ft_puthexnumax(unsigned int pf);
int					ft_putunmath(unsigned int pf);
int					ft_putpointer(void *pf);
int					ft_selector(va_list pf, char const *str);

/* =[ Aux miniRT_libft ]==================================================== */

long long			ft_atol(const char *nptr);
void				free_double_pointer(char **dbpt);
float				ft_atof(char *number);

/* ========================================================================= */

#endif
