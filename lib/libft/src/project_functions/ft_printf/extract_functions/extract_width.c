/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:38:37 by eterman           #+#    #+#             */
/*   Updated: 2016/11/28 16:01:17 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_first_width(char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		while (src[i] == '.')
		{
			i++;
			while (ft_isdigit(src[i]))
				i++;
		}
		if (ft_isdigit(src[i]) && src[i] != '0')
			return (ft_atoi(src + i));
		i++;
	}
	return (0);
}

void		extract_width(char *src, t_formats *formats, va_list *ap)
{
	char	*star_addr;

	star_addr = ft_strchr(src, '*');
	while (star_addr != NULL)
	{
		if (star_addr == src || star_addr[-1] != '.')
		{
			formats->width = va_arg(*ap, int);
			return ;
		}
		star_addr = ft_strchr(star_addr + 1, '*');
	}
	formats->width = get_first_width(src);
}
