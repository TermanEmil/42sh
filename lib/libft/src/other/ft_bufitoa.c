/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bufitoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:14:34 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 13:32:54 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Transforms a number into string, saved in buff.
*/

char	*ft_bufitoa(long long n, char *buf)
{
	unsigned long long	nb;
	char				*aux;

	*buf = 0;
	aux = buf;
	if (n < 0)
	{
		nb = (unsigned long long)(-1 * n);
		*aux = '-';
		aux++;
	}
	else
		nb = (unsigned long long)n;
	if (nb == 0)
		return (ft_strcpy(buf, "0"));
	while (nb != 0)
	{
		*aux = (char)(nb % 10 + 48);
		nb = nb / 10;
		aux++;
	}
	*aux = '\0';
	(*buf == '-') ? (ft_strrev(buf + 1)) : (ft_strrev(buf));
	return (buf);
}
