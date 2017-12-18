/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:54 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:54 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_char;
	unsigned char	*src_char;

	dest_char = (unsigned char*)dest;
	src_char = (unsigned char*)src;
	while (n)
	{
		n--;
		dest_char[n] = src_char[n];
	}
	return (dest);
}
