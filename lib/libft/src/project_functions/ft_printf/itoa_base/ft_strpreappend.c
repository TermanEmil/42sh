/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_frontadd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:26:32 by eterman           #+#    #+#             */
/*   Updated: 2016/12/01 17:50:42 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strpreappend(char **str, const char *content)
{
	char	*new_str;

	if (*str != NULL && content != NULL)
	{
		new_str = ft_strnew(ft_strlen(*str) + ft_strlen(content));
		ft_strcpy(new_str, content);
		ft_strcat(new_str, *str);
		free(*str);
		*str = new_str;
	}
}
