/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:03 by eterman           #+#    #+#             */
/*   Updated: 2016/10/24 18:56:46 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dst_size)
{
	char	*dest_end;
	size_t	i;
	size_t	bytes_to_copy;
	size_t	len;

	len = ft_strlen(dest);
	if (dst_size <= len + 1 || dst_size == 0)
		return (dst_size + ft_strlen(src));
	dest_end = ft_strend(dest);
	bytes_to_copy = dst_size - len - 1;
	i = 0;
	while (i < bytes_to_copy && src[i])
	{
		dest_end[i] = src[i];
		i++;
	}
	dest_end[i] = '\0';
	return (len + ft_strlen(src));
}
