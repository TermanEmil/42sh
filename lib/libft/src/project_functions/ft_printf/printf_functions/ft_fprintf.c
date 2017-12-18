/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 15:08:04 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 15:36:14 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_fprintf(int fd, const char *format, ...)
{
	va_list		ap;
	int			result;
	t_data		*data;

	data = sprintf_new_data();
	va_start(ap, format);
	process_format(format, &ap, data);
	va_end(ap);
	result = data->printed_chars - data->not_counted_chars;
	if (data->str)
	{
		write(fd, data->str, data->printed_chars);
		free(data->str);
	}
	free(data);
	return (result);
}
