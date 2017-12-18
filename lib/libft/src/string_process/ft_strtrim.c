/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:09 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:09 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** this function returns the RIGHT-'trimed' len of s
*/

static unsigned int	ft_count_trim_len(char const *s)
{
	unsigned int	result;

	result = 0;
	if (*s == '\0')
		return (0);
	result = ft_strlen(s);
	s += result - 1;
	while (ft_strchr(" \n\t", *s))
	{
		s--;
		result--;
	}
	return (result);
}

char				*ft_strtrim(char const *s)
{
	char			*result;
	unsigned int	trimed_len;

	if (!s)
		return (NULL);
	while (ft_strchr(" \n\t", *s))
		s++;
	trimed_len = ft_count_trim_len(s);
	result = (char*)malloc(trimed_len + 1);
	if (result == NULL)
		return (NULL);
	result[trimed_len] = '\0';
	while (trimed_len)
	{
		trimed_len--;
		result[trimed_len] = s[trimed_len];
	}
	return (result);
}
