/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_formats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:11:24 by eterman           #+#    #+#             */
/*   Updated: 2016/11/18 18:42:14 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_formats	*new_formats(void)
{
	t_formats		*result;

	if ((result = (t_formats*)malloc(sizeof(t_formats))) == NULL)
		return (NULL);
	result->width = 0;
	result->precision = 0;
	result->precision_specified = 0;
	result->specifier = '\0';
	result->to_print = NULL;
	result->null_arg = 0;
	return (result);
}

int			free_t_formats(t_formats **src)
{
	if (*src != NULL)
	{
		if ((*src)->to_print != NULL)
			free((*src)->to_print);
		free(*src);
	}
	return (-1);
}
