/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_is_utf8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:57:27 by eterman           #+#    #+#             */
/*   Updated: 2017/05/29 18:01:49 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline t_bool	chars_are_folow_uni(const unsigned char *chars)
{
	while (*chars)
	{
		if ((*chars >> 6) != 0x2)
			return (FALSE);
		chars++;
	}
	return (TRUE);
}

/*
** Checks if the given string is a valid utf8 string and returns the number of
** bytes it has. Otherwise returns 0.
*/

int					char_is_utf8(unsigned char const * const key)
{
	size_t		required_len;
	
	if (key[0] >> 7 == 0)
		required_len = 1;
	else if (key[0] >> 5 == 0x6)
		required_len = 2;
	else if (key[0] >> 4 == 0xE)
		required_len = 3;
	else if (key[0] >> 5 == 0x1E)
		required_len = 4;
	if (ft_strlen((char*)key) == required_len && chars_are_folow_uni(key + 1))
		return (required_len);
	else
		return (0);
}
