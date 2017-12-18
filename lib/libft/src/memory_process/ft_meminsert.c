/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meminsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:23:12 by eterman           #+#    #+#             */
/*   Updated: 2017/04/10 09:59:03 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Inserts content at the beginning of ptr.
** Be sure that ptr has enough memory.
** ptr_size is the size after x.
** Usesage: ft_meminsert(str + x, "emil", ft_strlen(str + x), 4);
*/

void	ft_meminsert(void *ptr, void *content, size_t ptr_size, size_t n)
{
	if (ptr && content)
	{
		ft_memmove(ptr + n, ptr, ptr_size);
		ft_memcpy(ptr, content, n);
	}
}
