/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_formats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 17:18:03 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 17:49:03 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define POSSIBLE_CHARS "lhjzL0123456789.*# -+"

/*
**	void		show_formats(t_formats *formats)
**	{
**		printf("flags:%s\n", formats->flags);
**		printf("width:%d\n", formats->width);
**		printf("precision:%d\n", formats->precision);
**		printf("length:%s\n", formats->length);
**		printf("specifier:%c\n", formats->specifier);
**		printf("__________\n\n");
**	}
*/

/*
** ft_strndup(*format, i + 2); one for the specifier, another for '\0'
*/

int			extract_fromats(CHR **format, va_list *ap, t_formats *formats)
{
	char	*percent_to_spec;
	int		i;

	i = 0;
	while (ft_strchr(POSSIBLE_CHARS, (*format)[i]) && (*format)[i])
		i++;
	percent_to_spec = ft_strndup(*format, i + 2);
	percent_to_spec[i + 1] = 0;
	extract_flags(percent_to_spec, formats);
	extract_width(percent_to_spec, formats, ap);
	extract_precision(percent_to_spec, formats, ap);
	extract_length(percent_to_spec, formats);
	extract_specifier(percent_to_spec, formats);
	free(percent_to_spec);
	if (formats->specifier == '\0')
		formats->specifier = (*format)[i];
	if (formats->specifier == '\0')
	{
		*format = &((*format)[i]);
		return (-1);
	}
	*format = &((*format)[i + 1]);
	return (1);
}
