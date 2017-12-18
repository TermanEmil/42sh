/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 14:42:30 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 15:56:05 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	int			result;
	t_data		*data;

	va_start(ap, format);
	data = sprintf_new_data();
	process_format(format, &ap, data);
	va_end(ap);
	result = data->printed_chars - data->not_counted_chars;
	if (data->str)
	{
		write(1, data->str, data->printed_chars);
		free(data->str);
	}
	free(data);
	return (result);
}
