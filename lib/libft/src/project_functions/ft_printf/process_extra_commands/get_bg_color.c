/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bg_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:26:37 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 11:56:07 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_bg_color(char *input, va_list *ap)
{
	int		index;
	char	*rs;

	if (ft_strequ(input, "") || !ft_strnequ(input, "bg_", 3))
		return (NULL);
	index = ft_index_of_word(input + 3, TCOLORS, " \n");
	if (index != -1)
		return (ft_strdup(ft_textcmd(index + 40)));
	if (ft_strnequ(input + 3, "rgb", 3))
	{
		if (ft_strequ(input + 6, "$"))
			ft_bufitoa((long long)va_arg(*ap, int), input + 6);
		if ((rs = get_rgb_color(input + 3, "48")))
			return (rs);
	}
	return (NULL);
}
