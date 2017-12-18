/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_utf8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 11:05:07 by eterman           #+#    #+#             */
/*   Updated: 2016/12/28 11:31:57 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_wstrlen(wchar_t *str)
{
	wchar_t		*start;

	start = str;
	while (*str)
		str++;
	return (str - start);
}

/*
** Transforms a wchar to utf-8, returning a string of converted bytes
*/

void			ft_to_utf8(wchar_t c, t_uchar *buffer)
{
	if (c < (1 << 7))
		*buffer++ = (unsigned char)(c);
	else if (c < (1 << 11))
	{
		*buffer++ = (unsigned char)((c >> 6) | 0xC0);
		*buffer++ = (unsigned char)((c & 0x3F) | 0x80);
	}
	else if (c < (1 << 16))
	{
		*buffer++ = (unsigned char)((c >> 12) | 0xE0);
		*buffer++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		*buffer++ = (unsigned char)((c & 0x3F) | 0x80);
	}
	else if (c < (1 << 21))
	{
		*buffer++ = (unsigned char)((c >> 18) | 0xF0);
		*buffer++ = (unsigned char)(((c >> 12) & 0x3F) | 0x80);
		*buffer++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		*buffer++ = (unsigned char)((c & 0x3F) | 0x80);
	}
	*buffer = '\0';
}

/*
** This function returns a fresh string converted to utf8
** First, I create a very big string (maximum possible of nb_bytes).
** Then, I append each wchar to it
** If no precision is specified, set nb_bytes = -1
*/

char			*ft_str_to_utf8(wchar_t *wstr, int nb_bytes)
{
	char	*str;
	int		len;
	t_uchar	wchar_buff[5];

	if (nb_bytes == -1)
		nb_bytes = ft_wstrlen(wstr) * sizeof(wchar_t);
	str = (char*)malloc(sizeof(char) * nb_bytes + 1);
	*str = '\0';
	while (*wstr)
	{
		ft_to_utf8(*wstr, wchar_buff);
		len = ft_strlen((char*)wchar_buff);
		if (nb_bytes - len >= 0)
		{
			ft_strcat(str, (char*)wchar_buff);
			nb_bytes -= len;
		}
		else
			break ;
		wstr++;
	}
	return (ft_strrealoc(&str));
}
