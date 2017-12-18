/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ddatainit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:22:19 by eterman           #+#    #+#             */
/*   Updated: 2017/05/30 12:09:08 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ddatainit(
			t_ddata *ddata,
			void *content,
			size_t size,
			size_t d_size)
{
	if (ddata != NULL)
	{
		ddata->content = content;
		ddata->size = size;
		ddata->d_size = d_size;
	}
}
