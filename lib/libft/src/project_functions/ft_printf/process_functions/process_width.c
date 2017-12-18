/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 20:23:46 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 20:23:48 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_zero_flag(t_formats *formats)
{
	if (formats->precision_specified && ft_strchr(NUM_SPEC, formats->specifier))
		return (0);
	if (ft_strchr(formats->flags, '0') && !ft_strchr(formats->flags, '-'))
		return (1);
	return (0);
}

/*
** It can be negative if the width is passed through *
*/

void		process_negative_width(t_formats *formats)
{
	if (formats->width < 0)
	{
		if (ft_strchr(formats->flags, '-') == NULL)
			ft_strcat(formats->flags, "-");
		formats->width *= -1;
	}
}

int			is_null_char_byte(t_formats *formats)
{
	return (ft_tolower(formats->specifier) == 'c' && formats->null_arg);
}

void		process_width(char **str, t_formats *formats)
{
	int		len;
	char	*result;
	char	filler;

	len = ft_strlen(*str) + is_null_char_byte(formats);
	filler = (is_zero_flag(formats)) ? ('0') : (' ');
	process_negative_width(formats);
	if (formats->width > len)
	{
		len = formats->width - len;
		result = ft_strnew(formats->width + (formats->null_arg));
		if (ft_strchr(formats->flags, '-') != NULL)
		{
			ft_strcpy(result + formats->null_arg, *str);
			strcat_chars(result + formats->null_arg, len, filler);
		}
		else
		{
			strcat_chars(result, len, filler);
			ft_strcat(result, *str);
		}
		free(*str);
		*str = result;
	}
}
