/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:03:31 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/29 12:44:15 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdarg.h>

/*
** Linked lists functions (BONUS)
*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list		*ft_lstnew(void *content);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*
** Functions from <ctype.h> library
*/

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_islower(int c); //*
int			ft_isupper(int c); //*
int			ft_isxdigit(int c); //*
int			ft_isspace(int c); //*
int			ft_isgraph(int c); //*
int			ft_isblank(int c); //*
int			ft_ispunct(int c); //*
int			ft_iscntrl(int c); //*

/*
** Functions from <stdlib.h> library
*/

int			ft_atoi(const char *str);
void		*ft_calloc(size_t nitems, size_t size);
double		ft_atof(const char *str); //*
long		ft_atol(const char *str); //*

/*
** Functions from <strings.h> library
*/

void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *dest, int c, size_t count);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *str1, const void *str2, size_t n);
void		*ft_memchr(const void *str, int c, size_t n);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);

/*
** Functions from <string.h> library
*/

size_t		ft_strlen(const char *c);
size_t		ft_strlen_2d(char **s); //*
char		*ft_strstr(const char *haystack, const char *needle); //*
size_t		ft_strlcpy(char *dest, const char *src, size_t n);
size_t		ft_strlcat(char *dest, const char *src, size_t n);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
int			ft_strcmp(const char *s1, const char *s2); //*
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t n); //*
char		*ft_strcat(char *s1, const char *s2); //*
char		*ft_strncat(char *s1, const char *s2, size_t n); //*
int			ft_strnrcmp(const char *s1, const char *s2, size_t n);

/*
** Functions from <math.h> library
*/

double		ft_sqrt(double x); //*
long double	ft_pow(long double n, unsigned int pow); //*

/*
** Non-standard functions
*/

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_swap(int *a, int *b); //*
void		ft_putchar(char c); //*
void		ft_putstr(char *s); //*
void		ft_putendl(char *s); //*
void		ft_putnbr(int n); //*
void		ft_split_free(char **s); //*

/*
** ft_printf functions
*/

int			ft_printf(const char *str, ...);
int			param_detector(va_list args, char c);
int			param_string(char *string);
int			param_pointer(unsigned long long ptr);
int			param_decimal(int proof);
int			param_unsdecimal(unsigned int num);
int			param_hex(unsigned int num, char c);
int			param_char(char character);
int			hex_len(unsigned int num);
void		ft_print_hex(unsigned int num, const char c);

/*
** get_next_line functions
*/

char		*get_next_line(int fd);
size_t		ft_strlen_gnl(const char *str);
char		*ft_strchr_gnl(const char *s, int c);
char		*ft_strjoin_gnl(char *static_buffer, char *temp);
char		*ft_firstline(char *string);
char		*ft_secondline(char *string);

#endif // LIBFT_H;