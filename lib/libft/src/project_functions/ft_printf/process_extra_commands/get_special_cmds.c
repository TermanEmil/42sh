/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_special_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:31:08 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 12:00:08 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** g_null will be returned for few cases
*/

char		*get_special_cmds(char *input, t_data *data)
{
	int			aux;

	aux = data->color_should_clean;
	data->color_should_clean = 1;
	if (ft_strequ(input, "underscore") || ft_strequ(input, "u"))
		return (ft_strdup(ft_textcmd(4)));
	if (ft_strequ(input, "bold") || ft_strequ(input, "b"))
		return (ft_strdup(ft_textcmd(1)));
	if (ft_strequ(input, "strike"))
		return (ft_strdup(ft_textcmd(9)));
	data->color_should_clean = aux;
	if (ft_strequ(input, "clear") || ft_strequ(input, "cl"))
		return (get_clrscr());
	if (ft_strequ(input, "cl_nocount") || ft_strequ(input, "#n"))
		return (get_color_nocount(data));
	if (ft_strequ(input, "cl_count") || ft_strequ(input, "#c"))
		return (get_color_count(data));
	if (ft_strequ(input, "eoc") || ft_strequ(input, "rs"))
		return (get_color_reset(data));
	return (NULL);
}
