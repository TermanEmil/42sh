/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_printed_chars.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 20:18:33 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 20:18:35 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			calculate_printed_chars(t_formats *formats)
{
	if (ft_tolower(formats->specifier) == 'c' && formats->null_arg)
	{
		if (ft_strchr(formats->flags, '-'))
			return (ft_strlen(formats->to_print + 1) + 1);
		else
			return (ft_strlen(formats->to_print) + 1);
	}
	return (ft_strlen(formats->to_print));
}
