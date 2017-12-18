/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:28:56 by eterman           #+#    #+#             */
/*   Updated: 2016/11/28 16:57:06 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		get_first_precision(char *src, t_formats *formats)
{
	int		i;

	i = 0;
	while (src[i])
	{
		while (ft_isdigit(src[i]))
			i++;
		if (src[i] == '.')
		{
			formats->precision_specified = 1;
			formats->precision = ft_atoi(src + i + 1);
			return ;
		}
		i++;
	}
	formats->precision_specified = 0;
	formats->precision = -1;
}

void		extract_precision(char *src, t_formats *formats, va_list *ap)
{
	char	*star_addr;

	star_addr = ft_strchr(src, '*');
	while (star_addr != NULL)
	{
		if (star_addr != src && star_addr[-1] == '.')
		{
			formats->precision = va_arg(*ap, int);
			formats->precision_specified = 1;
			return ;
		}
		star_addr = ft_strchr(star_addr + 1, '*');
	}
	get_first_precision(src, formats);
}
