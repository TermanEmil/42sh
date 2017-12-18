/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 20:29:59 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 20:30:15 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "itoa_base.h"

/*
** "%#.o", 0 will result in printing a zero whilst "%#.x", 0 won't print
** anything, so, I need that extra char for this case
*/

static int	octal_flag_exception(t_formats *formats)
{
	return (ft_strchr(formats->flags, '#') != NULL &&
			ft_tolower(formats->specifier) == 'o');
}

void		process_precision(char **str, t_formats *formats, char filler)
{
	int		len;
	char	*result;
	int		is_signed;

	if (formats->precision_specified)
	{
		len = ft_strlen(*str) + octal_flag_exception(formats);
		is_signed = ft_strchr("+-", **str) != NULL;
		if (is_signed)
			len--;
		if (formats->precision == 0 && ft_str_madeof_char(*str, '0'))
			**str = '\0';
		else if (formats->precision > len)
		{
			result = ft_strnew(formats->precision + is_signed);
			if (is_signed)
				*result = **str;
			strcat_chars(result, formats->precision - len, filler);
			ft_strcat(result, *str + is_signed);
			free(*str);
			*str = result;
		}
	}
}
