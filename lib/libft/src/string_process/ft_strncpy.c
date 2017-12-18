/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:05 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:05 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (dest);
	while (src[i])
	{
		if (i >= n)
			return (dest);
		dest[i] = src[i];
		i++;
	}
	while (i < n && dest[i])
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
