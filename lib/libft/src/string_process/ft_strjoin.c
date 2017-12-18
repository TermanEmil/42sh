/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:03 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:03 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	unsigned int	s1_len;
	unsigned int	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char*)malloc(s1_len + s2_len + 1);
	if (result == NULL)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcpy(result + s1_len, s2);
	return (result);
}
