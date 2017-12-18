/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:07 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:07 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strrchr() function returns a pointer to the last occurrence of the
** character c in the string s.
*/

char	*ft_strrchr(const char *s, int c)
{
	char	*occ;
	char	c_c;

	occ = NULL;
	c_c = (char)c;
	while (*s)
	{
		if (*s == c_c)
			occ = (char*)s;
		s++;
	}
	if (*s == c_c)
		occ = (char*)s;
	return (occ);
}
