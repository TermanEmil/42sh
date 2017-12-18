/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 15:06:25 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 15:35:25 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_sprintf(char **buff, const char *format, ...)
{
	va_list		ap;
	int			result;
	t_data		*data;

	data = sprintf_new_data();
	va_start(ap, format);
	process_format(format, &ap, data);
	va_end(ap);
	result = data->printed_chars - data->not_counted_chars;
	*buff = data->str;
	free(data);
	return (result);
}
