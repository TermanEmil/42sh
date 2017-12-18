/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:31:29 by eterman           #+#    #+#             */
/*   Updated: 2016/12/01 13:54:29 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				is_wchar(t_formats *formats)
{
	return (ft_strequ(formats->length, "l") ||
		ft_strequ(formats->length, "ll") ||
		ft_strchr("SC", formats->specifier));
}

static void		process_chr_precision(char **str, t_formats *formats)
{
	if (formats->precision_specified && formats->precision >= 0)
	{
		if (formats->precision < (int)ft_strlen(*str))
		{
			(*str)[formats->precision] = '\0';
			ft_strrealoc(str);
		}
	}
}

char			*process_simple_string(va_list *ap, t_formats *formats)
{
	char		*str;

	if ((str = va_arg(*ap, char*)) == NULL)
	{
		str = ft_strdup("(null)");
		formats->null_arg = 1;
	}
	else
	{
		str = ft_strdup(str);
		formats->null_arg = 0;
	}
	process_chr_precision(&str, formats);
	return (str);
}

char			*process_simple_chars(va_list *ap, t_formats *formats)
{
	char		*str;

	if (formats->specifier == 'c')
	{
		str = ft_strnew(1);
		*str = va_arg(*ap, int);
		if (*str == '\0')
			formats->null_arg = 1;
	}
	else if (formats->specifier == 's')
		str = process_simple_string(ap, formats);
	else
	{
		str = ft_strnew(1);
		*str = formats->specifier;
	}
	return (str);
}

char			*process_chars(va_list *ap, t_formats *formats)
{
	if (!formats->precision_specified)
		formats->precision = -1;
	if (is_wchar(formats))
		return (process_wchars(ap, formats));
	else
		return (process_simple_chars(ap, formats));
}
