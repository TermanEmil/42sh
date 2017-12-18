/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ddata_sizeadd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 00:42:56 by eterman           #+#    #+#             */
/*   Updated: 2017/01/22 01:10:16 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Simply adds a delta_size to it;
*/

void	*ft_ddata_sizeadd(t_ddata *ddata)
{
	if (ft_ddatarealloc(ddata, ddata->size + ddata->d_size) == ENOMEM)
		return (NULL);
	else
		return (ddata->content);
}
