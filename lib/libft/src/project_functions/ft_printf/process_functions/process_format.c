/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 15:54:01 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 15:54:02 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				process_percent(CHR **format, va_list *ap, t_data *data)
{
	t_formats	*formats;

	(*format)++;
	formats = new_formats();
	if (extract_fromats(format, ap, formats) == -1)
		return (free_t_formats(&formats) + 0);
	if (ft_strchr(NUM_SPEC, formats->specifier) != NULL)
		formats->to_print = formats_itoa_base(ap, formats);
	else if (formats->specifier == 'n')
	{
		process_n_specifier(ap, data);
		return (free_t_formats(&formats) + 0);
	}
	else
		formats->to_print = process_chars(ap, formats);
	process_width(&(formats->to_print), formats);
	sprintf_add_data(data, formats->to_print, calculate_printed_chars(formats));
	return (free_t_formats(&formats) + 1);
}

void			process_simple_words(CHR **format, t_data *data)
{
	int			i;

	i = 0;
	while (!ft_strchr("\045{", (*format)[i]) && (*format)[i])
		i++;
	sprintf_add_data(data, *format, i);
	(*format) += i;
}

void			process_format(CHR *format, va_list *ap, t_data *data)
{
	while (1)
	{
		process_simple_words(&format, data);
		if (*format == '%')
			process_percent(&format, ap, data);
		else if (*format == '{')
			detect_process_extra_cmds(ap, data, &format);
		else if (*format == 0)
			return (detect_process_extra_cmds(ap, data, &format));
		else
			format++;
	}
}
