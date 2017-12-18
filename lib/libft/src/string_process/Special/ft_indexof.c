/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:18:52 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 13:36:02 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the index of 'str' in 'table'.
** '-1' if it can't find it.
*/

int			ft_indexof(char **table, char *str)
{
	int		index;

	if (table == NULL || str == NULL)
		return (-1);
	index = 0;
	while (table[index])
	{
		if (ft_strequ(table[index], str))
			return (index);
		index++;
	}
	return (-1);
}
