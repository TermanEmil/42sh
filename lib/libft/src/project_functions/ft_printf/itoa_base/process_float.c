/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:28:02 by eterman           #+#    #+#             */
/*   Updated: 2016/12/27 16:55:32 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*process_double(va_list *ap, t_formats *formats)
{
	return (ft_ftoa((double)va_arg(*ap, double), formats->precision));
}

char		*process_ldouble(va_list *ap, t_formats *formats)
{
	return (ft_ftoa((double)va_arg(*ap, t_ld), formats->precision));
}

char		*process_float(va_list *ap, t_formats *formats)
{
	char	*result;

	if (!formats->precision_specified)
		formats->precision = 6;
	if (ft_strstr(formats->length, "L"))
		result = process_ldouble(ap, formats);
	else
		result = process_double(ap, formats);
	if (formats->specifier == 'F')
		ft_str_toupper(result);
	else
		ft_str_tolower(result);
	return (result);
}
