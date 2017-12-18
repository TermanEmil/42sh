/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:06 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:06 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	s_len;
	char	*rs;
	size_t	zero_byte;

	s_len = ft_strlen(s);
	if (s_len < n)
		zero_byte = 0;
	else
		zero_byte = 1;
	rs = (char*)malloc(n + zero_byte);
	if (rs == NULL)
		return (NULL);
	if (s_len < n)
		rs[s_len] = '\0';
	else
		rs[n] = '\0';
	while (n)
	{
		n--;
		rs[n] = s[n];
	}
	return (rs);
}
