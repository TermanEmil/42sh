/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:08 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:08 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_first_strstr(const char *str, const char *substr)
{
	size_t	i;

	i = 1;
	while (substr[i] == str[i] && substr[i])
		i++;
	return (substr[i] == '\0');
}

char			*ft_strstr(const char *str, const char *substr)
{
	if ((*str == '\0' && *substr == '\0') || *substr == '\0')
		return ((char*)str);
	while (*str)
	{
		if (*str == *substr && ft_first_strstr(str, substr))
			return ((char*)str);
		str++;
	}
	return (NULL);
}
