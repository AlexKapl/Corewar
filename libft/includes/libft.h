/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:07:31 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 18:51:04 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "hsv.h"
# include "ft_printf.h"
# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 100

# define INTMAX 0x7fffffff
# define INTMIN 0xffffffff

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define NONE 0
# define FIRST 1
# define SECOND 2
# define BOTH 3

/*
**		Boolean define
*/
# ifndef T_BOOL
#  define T_BOOL
#  define TRUE 1
#  define FALSE 0

typedef char		t_bool;
# endif

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

unsigned			ft_bit_swap(unsigned u);
unsigned long long	ft_bit_swap_ll(unsigned long long llu);
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew_struct(void const *content, size_t content_size,
								int (*f)(void const *, size_t, t_list **));
void				ft_lstadd(t_list **alst, t_list *new_node);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lst_sort(t_list **begin, int (*f)(void *e1, void *e2),
								int count, int max);
void				ft_lst_sort_size(t_list **begin,
						int (*f)(size_t e1, size_t e2), int count, int max);
void				ft_lst_push_back(t_list **alst, t_list *new_node);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *restrict dst, const void *restrict src,
								size_t n);
void				*ft_memccpy(void *restrict d, const void *restrict s,
								int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memalloc(size_t size);
void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(const char *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_bzero(void *str, size_t n);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_strcapitalizer(char *str);
void				ft_int_sort(int *tab, size_t size);
void				ft_tabdel(char **tab, int count);
int					ft_tabcount(char **tab);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, int base);
int					ft_abs(int x);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isspace(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_intlen(long long num);
int					ft_space_skip_i(char *str);
int					ft_strisdigit(const char *str);
int					ft_strcount(const char *str, char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
int					get_next_line(int const fd, char **line);
size_t				ft_strlen(const char *s);
size_t				ft_lstcount(t_list *begin);
size_t				ft_strlcat(char *restrict dst, const char *restrict src,
								size_t size);
char				*ft_strnew(size_t size);
char				*ft_strdup(const char *s1);
char				*ft_readfile(const int fd);
char				*ft_llitoa(intmax_t value);
char				*ft_llitoa_base(uintmax_t value, int base);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *restrict s1, const char *restrict s2);
char				*ft_strncat(char *restrict s1, const char *restrict s2,
								size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchr_space(const char *s);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little,
								size_t len);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s);
char				*ft_strrev(char *str);
char				*ft_space_skip(char *str);
char				*ft_realloc(char *str, size_t len);
char				**ft_strsplit(const char *s, char c);
char				*ft_strmake(char *s1, char *s2, int del);
char				*ft_strconcat(int count, ...);

/*
**					stack/queue functions
*/
int					stack_push(t_list **stack, void *item, size_t size);
void				*stack_pop(t_list **stack);
void				*stack_peek(t_list **stack);
int					enqueue(t_list **queue, void *item, size_t size);
void				*dequeue(t_list **queue);
void				*queue_peek(t_list **queue);

#endif
