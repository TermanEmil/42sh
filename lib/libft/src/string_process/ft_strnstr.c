/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:07 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:07 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_first_strstr(const char *str, const char *substr, size_t len)
{
	size_t	i;

	i = 0;
	while (substr[i] == str[i] && substr[i] && i < len)
		i++;
	return (substr[i] == '\0');
}

char			*ft_strnstr(const char *str, const char *substr, size_t len)
{
	while (*str && len)
	{
		if (ft_first_strstr(str, substr, len))
			return ((char*)str);
		str++;
		len--;
	}
	return (NULL);
}
