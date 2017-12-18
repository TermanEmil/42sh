/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_wchars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 20:21:36 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 20:21:38 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*process_wchars(va_list *ap, t_formats *formats)
{
	char		*str;
	wchar_t		*wstr;
	t_uchar		buff[5];

	if (ft_tolower(formats->specifier) == 'c')
	{
		ft_to_utf8(va_arg(*ap, wchar_t), buff);
		str = ft_strdup((char*)buff);
		formats->null_arg = (*str == '\0') ? (1) : (0);
	}
	else
	{
		wstr = va_arg(*ap, wchar_t*);
		if (wstr == NULL)
		{
			str = ft_str_to_utf8(L"(null)", formats->precision);
			formats->null_arg = 1;
		}
		else
		{
			formats->null_arg = 0;
			str = ft_str_to_utf8(wstr, formats->precision);
		}
	}
	return (str);
}
