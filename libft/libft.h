/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 12:32:14 by npiatiko          #+#    #+#             */
/*   Updated: 2018/11/22 11:19:11 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 32
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

typedef enum	e_modifier
{
	hh = 10,
	h = 20,
	l = 30,
	ll = 40,
	L = 50
}				t_modifier;

typedef struct		s_specifier
{
	char			tp;
	int				fl_pl;
	int				fl_mn;
	int				fl_zr;
	int				fl_sh;
	int				fl_sp;
	int				wd;
	int				prc;
	t_modifier		mdr;
}					t_specifier;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack,
	const char *needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_list_push_back(t_list **lst, t_list *new);
void			ft_print_bits(unsigned char octet);
size_t			ft_list_size(t_list *begin_list);
void			ft_print_list(t_list *lst);
void			ft_list_reverse(t_list **begin_list);
int				get_next_line(const int fd, char **line);
char			*ft_joinstr(const char *s1, const char *s2);
int				ft_printf(const char *restrict format, ...);
char			*ft_itoabase_u(unsigned long long int nbr, int base);
int				ft_fvprintf(va_list va, char *format);
char			*ft_print_o(t_specifier *spec, long long int nbr);
char			*ft_strnew_chr(size_t len, char c);
char			*ft_print_x(t_specifier *spec, long long nbr);
void			initspecifier(t_specifier *spec, char **format, va_list va);
char			*ft_joinchar(char *str, char c);
int				ft_print_c(t_specifier *spec, long long nbr);
char			*ft_print_s(t_specifier *spec, char *ptr);
char			*ft_print_p(t_specifier *spec, long long nbr);
char			*ft_print_u(t_specifier *spec, long long nbr);
char			*ft_lltoa(long long nbr);
char			*ft_print_di(t_specifier *spec, long long nbr);
int				ft_nbrlen(int num);
void			resetspecifier(t_specifier *spec);
char			*ft_print_double(t_specifier *spec, long double nbr);
char			*ft_print_bin(t_specifier *spec, long long int data);

#endif
