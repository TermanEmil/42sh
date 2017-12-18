/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specials.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:32:50 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 11:55:00 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_color_nocount(t_data *data)
{
	data->color_count = 0;
	return ("");
}

char		*get_color_count(t_data *data)
{
	data->color_count = 1;
	return ("");
}

char		*get_color_reset(t_data *data)
{
	data->color_should_clean = 0;
	return (ft_strdup(ft_textcmd(0)));
}

char		*get_clrscr(void)
{
	return (ft_strdup("\x1b[2J\x1b[1;1H"));
}
