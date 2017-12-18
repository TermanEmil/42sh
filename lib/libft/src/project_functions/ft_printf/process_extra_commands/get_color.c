/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:35:27 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 11:55:47 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_color(char *input, va_list *ap)
{
	int		index;
	char	*rs;

	if (ft_strequ(input, ""))
		return (NULL);
	index = ft_index_of_word(input, TCOLORS, " \n");
	if (index != -1)
		return (ft_strdup(ft_textcmd(index + 30)));
	if (ft_strnequ(input, "rgb", 3))
	{
		if (ft_strequ(input + 3, "$"))
			ft_bufitoa((long long)va_arg(*ap, int), input + 3);
		if ((rs = get_rgb_color(input, "38")))
			return (rs);
	}
	return (NULL);
}
