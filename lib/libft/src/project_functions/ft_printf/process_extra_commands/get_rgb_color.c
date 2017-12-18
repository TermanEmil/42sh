/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 12:46:31 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 13:15:31 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** the format is: \033[38;5;108m where 38 and 48 is for color and bg_color
** and 108 is the actual color.
*/

char		*get_rgb_color(char *input, char *cl_or_bg)
{
	int		cl;
	char	buff[30];

	if (!ft_strnequ(input, "rgb", 3))
		return (NULL);
	cl = ft_atoi(input + 3);
	if (cl < 0 || cl > 256)
		return (NULL);
	ft_strcpy(buff, "\033[");
	ft_strcat(buff, cl_or_bg);
	ft_strcat(buff, ";5;");
	ft_strcat(buff, input + 3);
	ft_strcat(buff, "m");
	return (ft_strdup(buff));
}
