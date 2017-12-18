/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:59 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:59 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function which returns the address of the first occurence of c
** or, if it doesn't find it, it returns the address of the null
** char of the string
*/

char	*ft_strchrnul(const char *s, int c)
{
	char	c_c;

	c_c = (char)c;
	while (*s && *s != c_c)
		s++;
	return ((char*)s);
}
