/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strends_winth.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:51:25 by eterman           #+#    #+#             */
/*   Updated: 2017/02/19 11:58:20 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks if str ends with end.
*/

int			ft_strends_winth(char *str, char *end)
{
	size_t	s_len;
	size_t	e_len;

	s_len = ft_strlen(str);
	e_len = ft_strlen(end);
	if (s_len < e_len)
		return (0);
	return (ft_strequ(str + s_len - e_len, end));
}
