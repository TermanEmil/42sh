/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractlib.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 21:38:17 by eterman           #+#    #+#             */
/*   Updated: 2016/11/28 22:04:27 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACTLIB_H
# define EXTRACTLIB_H

# include "ft_printf.h"

# define CHR const char

int			extract_fromats(CHR **frmt, va_list *ap, t_formats *frmts);
void		extract_flags(char *src, t_formats *formats);
int			extract_number(CHR **str);
void		extract_width(char *src, t_formats *formats, va_list *ap);
void		extract_precision(char *src, t_formats *formats, va_list *ap);
void		extract_length(char *src, t_formats *formats);
void		extract_specifier(char *src, t_formats *formats);
void		show_formats(t_formats *formats);

#endif
