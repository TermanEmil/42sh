/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:53 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:53 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest_c;
	unsigned char	*src_c;
	unsigned char	c_c;
	unsigned int	i;

	c_c = (unsigned char)c;
	dest_c = (unsigned char*)dest;
	src_c = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		dest_c[i] = src_c[i];
		if (src_c[i] == c_c)
			return (&dest_c[i + 1]);
		i++;
	}
	return (NULL);
}
