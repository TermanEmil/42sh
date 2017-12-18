/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_specifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:36:10 by eterman           #+#    #+#             */
/*   Updated: 2016/11/28 19:07:10 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		extract_specifier(char *src, t_formats *formats)
{
	while (*src)
	{
		if (ft_strchr(SPECIFIERS, *src))
			formats->specifier = *src;
		src++;
	}
}
