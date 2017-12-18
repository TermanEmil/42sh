/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 22:39:52 by eterman           #+#    #+#             */
/*   Updated: 2016/12/25 23:00:32 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_short(char *src)
{
	char	*addr;

	while ((addr = ft_strstr(src, "hh")))
	{
		addr[0] = 'H';
		addr[1] = addr[0];
		addr = ft_strstr(addr + 1, "hh");
	}
	return (ft_strchr(src, 'h') != NULL);
}

/*
** Note, that 'is_short' transforms all hh into HH
** So %hhhd will be short (%HHhd)
*/

void		extract_length(char *src, t_formats *formats)
{
	formats->length[0] = 0;
	if (ft_strstr(src, "ll"))
		ft_strcpy(formats->length, "ll");
	else if (ft_strchr(src, 'z'))
		ft_strcpy(formats->length, "z");
	else if (ft_strchr(src, 'j'))
		ft_strcpy(formats->length, "j");
	else if (ft_strchr(src, 'l'))
		ft_strcpy(formats->length, "l");
	else if (is_short(src))
		ft_strcpy(formats->length, "h");
	else if (ft_strstr(src, "HH"))
		ft_strcpy(formats->length, "hh");
	else if (ft_strstr(src, "L"))
		ft_strcpy(formats->length, "L");
}
