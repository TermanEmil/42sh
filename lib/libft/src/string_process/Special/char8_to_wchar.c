/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char8_to_wchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 11:03:51 by eterman           #+#    #+#             */
/*   Updated: 2017/05/30 11:06:23 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t		char8_to_wchar(const unsigned char *c_str)
{
	wchar_t		c;
	
	switch (ft_strlen((char*)c_str))
	{
		case 1:
			c = c_str[0];
			break;
		case 2:
			c = ((c_str[0] >> 2) & 0x7) << 8;
			c |= ((c_str[0] & 0x3) << 6) | (c_str[1] & 0x3F);
			break;
		case 3:
			c = ((c_str[0] & 0xF) << 4) | ((c_str[1] >> 2) & 0xF);
			c = c << 8;
			c |= (c_str[1] << 6) | (c_str[2] & 0x3F);
			break;
		case 4:
			c = ((c_str[0] & 0x7) << 2) | ((c_str[1] >> 4) & 0x3);
			c = c << 8;
			c |= ((c_str[1] & 0xF) << 4) | ((c_str[2] >> 2) & 0xF);
			c = c << 8;
			c |= (c_str[2] << 6) | (c_str[3] & 0x3F);
			break;
	}
	return (c);
}
