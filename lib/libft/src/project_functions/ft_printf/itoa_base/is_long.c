/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 20:28:56 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 20:28:57 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "itoa_base.h"

/*
** Checks if the given format specifies long int
*/

int			is_long(t_formats *formats)
{
	return (ft_strequ(formats->length, "l") ||
		ft_strchr("DUBO", formats->specifier) != NULL);
}
