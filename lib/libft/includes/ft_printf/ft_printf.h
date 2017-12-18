/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:28:20 by eterman           #+#    #+#             */
/*   Updated: 2016/11/17 17:49:00 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <wchar.h>
# include "libft.h"
# include "t_formats.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include "extractlib.h"
# include <inttypes.h>
# include <limits.h>

# define SPECIFIERS	"\x25sScCbBoOuUidDxXpnfF"
# define NUM_SPEC	"bBoOuUidDxXpfF"
# define TCOLORS	"black red green yellow blue magenta cyan white"
# define BASE		"0123456789abcdef"
# define MY_ROUND_VAL 0.00000000000005

/*
** It also considers bg_ + color {bg_red}.
** bold || {b}, underscore || {u} and strikethrough || {strike}.
** {$cl} - to give arguments
** clear || cl - clears the display
** {cl_nocount} || {#n} - doesn't count chars written for collors
** {cl_count} || {#c} == -{cl_nocount}
** If some chars are not counted, it doesn't mean they are not printed.
** It works like this: write (fd, str, printed_chars),
** but printf and %n returns: printed_chars - not_counted_chars
** rgb123 || bg_rgb21 || "{rgb$}", 100 == {rgb100}
** Ex: ft_printf("{cl}{#n}{cyan}I {eoc}{bg_rgb$}{black}love{eoc} {$}{b}cookies
** {eoc} {red}{$}%s\n", 123, "strike", "underscore", "cursus42");
** Even something like: "{$}emil", "rgb$", 100 --> {rgb100}emil
*/

/*
** Note, if you modify the FLAGS, you should then modify the size of
** formats->flags[]
*/

typedef struct	s_data
{
	int			color_count;
	int			printed_chars;
	int			color_should_clean;
	char		*str;
	int			not_counted_chars;
}				t_data;

/*
** printf functions
*/

int				ft_printf(const char *format, ...);
int				ft_fprintf(int fd, const char *format, ...);
int				ft_sprintf(char **buff, const char *format, ...);
/*
** Constructor / destructor
*/

int				free_t_formats(t_formats **src);
t_data			*sprintf_new_data(void);
t_formats		*new_formats();

/*
** Kind of general libft functions
*/

char			*ft_str_toupper(char *str);
char			*ft_str_tolower(char *str);
int				is_wchar(t_formats *formats);
char			*ft_str_to_utf8(wchar_t *wstr, int nb_bytes);
void			ft_to_utf8(wchar_t c, t_uchar *buffer);
void			ft_strpreappend(char **str, const char *content);
char			*ft_strrealoc(char **str);
void			strcat_chars(char *str, int count, char c);
int				ft_str_madeof_char(char *str, char c);
int				ft_indexof(char **table, char *str);
char			*ft_bufitoa(long long n, char *buf);
void			ft_free_bidimens(char **table);
void			ft_memappend(char **str1, CHR *str2, int len1, int len2);

/*
** Float
*/
char			*ft_ftoa(long double n, int precision);
int				ft_isinf(double x);
int				ft_isnan(double x);
long double		ft_floor(long double n);
long double		ft_ceil(long double n);
long double		ft_round(long double n);
long double		ft_nround(long double n, int precision);

/*
** Colors
*/

void			detect_process_extra_cmds(va_list *ap, t_data *d, CHR **frmt);
void			sprintf_add_data(t_data *data, CHR *str2, int len2);
int				substract_cmd(CHR *format, char *buff, int max_len);
char			*get_color_nocount(t_data *data);
char			*get_color_count(t_data *data);
char			*get_color_reset(t_data *data);
char			*get_clrscr(void);
char			*get_color(char *input, va_list *ap);
char			*get_bg_color(char *input, va_list *ap);
char			*ft_textcmd(int index);
char			*get_special_cmds(char *input, t_data *data);
char			*get_rgb_color(char *input, char *cl_or_bg);

/*
** Process functions
*/

void			process_format(CHR *format, va_list *ap, t_data *data);
void			process_n_specifier(va_list *ap, t_data *data);
char			*process_chars(va_list *ap, t_formats *formats);
void			process_width(char **str, t_formats *formats);
void			process_precision(char **str, t_formats *frmts, char filer);
void			process_zero_flag(char **str, t_formats *formats);
char			*process_wchars(va_list *ap, t_formats *formats);
char			*process_float(va_list *ap, t_formats *formats);

/*
** Diez flag functions
*/

char			*diez_flag_to_append(t_formats *formats);
int				diez_on_when_nothing(char *str, t_formats *formats);
int				diez_flag_is_null(char *str, t_formats *formats);

/*
** Others
*/

char			*formats_itoa_base(va_list *ap, t_formats *formats);
int				calculate_printed_chars(t_formats *formats);

#endif
