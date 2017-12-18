/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:54 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:54 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void const *ptr, size_t size)
{
	void			*result;

	result = (void*)malloc(size);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, ptr, size);
	return (result);
}
