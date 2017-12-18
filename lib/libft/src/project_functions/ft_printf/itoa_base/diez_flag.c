/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diez_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 20:26:28 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 20:26:35 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "itoa_base.h"

#define O_BASE "bBoOxXp"

/*
** Returns 0 if str is "" only for oO
** Just didn't want to think more about it
*/

int			special_str_madeof_char(char *str, char c, t_formats *formats)
{
	if (formats->specifier == 'p')
		return (0);
	if (*str == '\0' && ft_strchr("oO", formats->specifier))
		return (0);
	while (*str)
	{
		if (*str != c)
			return (0);
		str++;
	}
	return (1);
}

char		*diez_flag_to_append(t_formats *formats)
{
	static char result[3];

	result[0] = '0';
	if (ft_toupper(formats->specifier) == 'O')
		result[1] = '\0';
	else
	{
		result[1] = formats->specifier;
		if (formats->specifier == 'p')
			result[1] = 'x';
		result[2] = '\0';
	}
	return (result);
}

int			diez_on_when_nothing(char *str, t_formats *formats)
{
	return (!ft_str_madeof_char(str, '0') &&
		(ft_strchr("xXbB", formats->specifier) != NULL && *str != '\0'));
}

int			diez_flag_is_null(char *str, t_formats *formats)
{
	if (ft_strchr(formats->flags, '#') != NULL)
		if (ft_strchr(O_BASE, formats->specifier) != NULL &&
			!special_str_madeof_char(str, '0', formats))
			return (0);
	return (1);
}
