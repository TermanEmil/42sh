/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_zero_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 20:30:43 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 20:30:44 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "itoa_base.h"

static int	zero_flag_is_on(t_formats *formats)
{
	if (ft_strchr(formats->flags, '0'))
		if (ft_strchr(formats->flags, '-') == NULL)
		{
			if (ft_tolower(formats->specifier) == 'f')
				return (1);
			else
				return (!formats->precision_specified);
		}
	return (0);
}

static int	byte_for_plus(char *str, t_formats *formats)
{
	return (ft_strchr(formats->flags, '+') && *str != '-');
}

/*
** "% 05d\n", 0
*/

static int	byte_for_space_flag_and_zero_nb(char *str, t_formats *formats)
{
	return (ft_strchr(formats->flags, ' ') && *str == '0');
}

void		process_zero_flag(char **str, t_formats *formats)
{
	int		len;
	char	*result;
	int		is_signed;

	if (zero_flag_is_on(formats))
	{
		len = ft_strlen(*str);
		len += byte_for_plus(*str, formats);
		len += byte_for_space_flag_and_zero_nb(*str, formats);
		if (!diez_flag_is_null(*str, formats))
			len += ft_strlen(diez_flag_to_append(formats));
		if (formats->width > len)
		{
			is_signed = ft_strchr("+-", **str) != NULL;
			len = formats->width - len;
			result = ft_strnew(formats->width);
			if (is_signed)
				*result = **str;
			strcat_chars(result, len, '0');
			ft_strcat(result, *str + is_signed);
			free(*str);
			*str = result;
		}
	}
}
