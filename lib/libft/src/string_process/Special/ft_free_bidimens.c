/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bidimens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:13:53 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 13:32:03 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_bidimens(char **table)
{
	int		i;

	if (table != NULL)
	{
		i = 0;
		while (table[i])
			free(table[i++]);
		free(table);
	}
}
