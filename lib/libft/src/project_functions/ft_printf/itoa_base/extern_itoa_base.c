/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_itoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:12:09 by eterman           #+#    #+#             */
/*   Updated: 2016/11/30 11:41:19 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "itoa_base.h"

/*
** Checks if  a string is made only of char c
*/

int			ft_str_madeof_char(char *str, char c)
{
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str != c)
			return (0);
		str++;
	}
	return (1);
}

void		process_plus_space_flags(char **str, t_formats *formats)
{
	if (ft_strchr("idDfF", formats->specifier) != NULL && **str != '-')
	{
		if (ft_strchr(formats->flags, '+') != NULL)
			ft_strpreappend(str, "+");
		else if (ft_strchr(formats->flags, ' ') != NULL)
			ft_strpreappend(str, " ");
	}
}

/*
** the flag '#' is ignored if *str is made only of 0
*/

void		process_flags(char **str, t_formats *formats)
{
	if (!diez_flag_is_null(*str, formats))
		ft_strpreappend(str, diez_flag_to_append(formats));
	process_plus_space_flags(str, formats);
}

int			find_out_which_base(t_formats *formats, char upper_specifier)
{
	int		base;

	if (upper_specifier == 'X')
		base = 16;
	else if (upper_specifier == 'P')
	{
		base = 16;
		if (ft_strchr(formats->flags, '#') == NULL)
			ft_strcat(formats->flags, "#");
		ft_strcpy(formats->length, "ll");
	}
	else if (upper_specifier == 'O')
		base = 8;
	else if (upper_specifier == 'B')
		base = 2;
	else
		base = 10;
	return (base);
}

/*
** Returns a new string transformed to the desired base.
** It takes in consideration the flags "#+" and considers the specifiers "bB"
*/

char		*formats_itoa_base(va_list *ap, t_formats *formats)
{
	int			base;
	char		spcs;
	char		*rs;

	spcs = ft_toupper(formats->specifier);
	base = find_out_which_base(formats, spcs);
	if (spcs == 'F')
		rs = process_float(ap, formats);
	else
		rs = va_arg_itoa(ap, base, spcs == formats->specifier, formats);
	process_precision(&rs, formats, '0');
	process_zero_flag(&rs, formats);
	process_flags(&rs, formats);
	return (rs);
}
