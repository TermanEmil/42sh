/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:53 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:53 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_c;
	unsigned char	c_c;
	size_t			i;

	c_c = (unsigned char)c;
	s_c = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (s_c[i] == c_c)
			return (&s_c[i]);
		i++;
	}
	return (NULL);
}
