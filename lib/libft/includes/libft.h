/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 00:37:36 by eterman           #+#    #+#             */
/*   Updated: 2017/06/22 19:03:36 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>
# include <limits.h>
# include "short_named_types.h"
# include "errno.h"

/*
** The makefile is possible hidden (.Makefile)
*/

# define CHR const char
# define FT_ABS(X)			((X < 0) ? (-X) : (X))
# define FT_SIGN_NOZERO(X)	((X < 0) ? (-1) : (1))
# define FT_SIGN(X)			((X == 0) ? (0) : (FT_SIGN_NOZERO(X)))
# define FT_MIN(X, Y)		((X < Y) ? (X) : (Y))
# define FT_MAX(X, Y)		((X > Y) ? (X) : (Y))

/*
** Error path
*/

# ifndef STDERR
#  define STDERR 2
# endif

# ifndef STDIN
#  define STDIN 0
# endif

# define CAST(a, t_type) ((t_type)(a))


/*
** Boolean defines
*/

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef int				t_bool;
typedef char			*t_str;
typedef char const	 	*t_rostr;

/*
** d_size - the size wich will be added if there's not
** enough space (delta size).
*/

typedef struct	s_ddata
{
	void		*content;
	size_t		size;
	size_t		d_size;
}				t_ddata;

typedef struct	s_str_pair
{
	char const	*first;
	char const	*second;
}				t_str_pair;

/*
** Project functions
*/

int				get_next_line(int const fd, char **line);
int				ft_printf(const char *format, ...);
int				ft_fprintf(int fd, const char *format, ...);
int				ft_sprintf(char **buff, const char *format, ...);

/*
**	Memory function
*/

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			*ft_memdup(void const *ptr, size_t size);
void			ft_meminsert(void *ptr, void *cnt, size_t ptr_size, size_t n);

/*
** String functions
*/

size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strchrnul(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *big, const char *lttl, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_ustrequ(const t_uchar *s1, const t_uchar *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char sep);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strend(char *s);
char			*ft_strrev(char *str);
char			*ft_str_tolower(char *str);
char			*ft_str_toupper(char *str);

/*
** Special (string)
*/

void			ft_free_bidimens(char **table);
char			*ft_strrealoc(char **str);
int				ft_wstrlen(wchar_t *str);
int				ft_indexof(char **table, char *str);
int				ft_index_of_word(char *word, char *str, char *delims);
char			**ft_strtok(char const *s, const char *sep);
char			*ft_strmegajoin(int argc, ...);
char			*ft_strnchr(const char *s, char *chars);
void			ft_strdelif(char **str);
char			*ft_strreplace(char *dest, char *target, const char *str);
int				ft_strends_winth(char *str, char *end);
int				ft_match(char const *s1, char const *s2);
void			ft_strrm_n(char *str, size_t index, size_t n);
int				ft_str_stack_cat(char *dest, char const *str, size_t dest_len);
void			ft_strncpy_terminate(char *dest, char const *str, size_t len);
t_str			ft_strnew_raw(size_t const len);

/*
** utf8
*/

void			ft_to_utf8(wchar_t c, t_uchar *buffer);
char			*ft_str_to_utf8(wchar_t *wstr, int nb_bytes);
int				char_is_utf8(const unsigned char *key);
char const		*utf8_get_first(unsigned char const * const key);
wchar_t			char8_to_wchar(const unsigned char *c_str);

/*
** t_ddata
*/

void			ft_ddatainit(
						t_ddata *ddata,
						void *content,
						size_t size,
						size_t d_size);
int				ft_ddatarealloc(t_ddata *ddata, size_t required_size);
void			*ft_ddata_sizeadd(t_ddata *ddata);

/*
** ctype.h functions
*/

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper (int c);
int				ft_tolower (int c);
int				ft_isupper(int c);
int				ft_islower(int c);

/*
** Print functions
*/

void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnewl();

/*
** Other
*/

int				ft_atoi(const char *str);
char			*ft_itoa(int n);
char			*ft_bufitoa(long long n, char *buf);
void			print_n_times(char *str, int n, int fd);
void			ft_print_mem(void const *ptr, size_t size, int base);
char const		*ft_char_to_str(char c);
char			ft_get_matching_parenthesis(char const parenthesis);
void			ft_pass(void);

/*
** Standard functions
*/

void			std_mem_del(void *mem, size_t mem_size);

#endif
