/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:58:16 by eterman           #+#    #+#             */
/*   Updated: 2017/01/15 21:21:06 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, char *chars)
{
	while (*s && ft_strchr(chars, *s) == NULL)
		s++;
	if (*s == 0)
		return (NULL);
	if (ft_strchr(chars, *s) != NULL)
		return ((char*)s);
	return (NULL);
}
