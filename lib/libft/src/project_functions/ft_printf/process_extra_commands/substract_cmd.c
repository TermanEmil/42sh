/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substract_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 15:53:43 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 15:53:45 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Used to substract extra command from {}
*/

int			substract_cmd(CHR *format, char *buff, int max_len)
{
	int		i;

	*buff = 0;
	i = 0;
	while (format[i])
	{
		if (i >= max_len)
			return (0);
		if (format[i] == '}')
		{
			buff[i] = 0;
			return (1);
		}
		buff[i] = format[i];
		i++;
	}
	return (0);
}
