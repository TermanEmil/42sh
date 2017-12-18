/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:05 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:05 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	char	*aux;

	i = 0;
	aux = ft_strend(dest);
	while (i < n && src[i])
	{
		aux[i] = src[i];
		i++;
	}
	aux[i] = '\0';
	return (dest);
}
