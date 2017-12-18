/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:50 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:50 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			buf[12];
	char			*aux;

	aux = buf;
	if (n < 0)
	{
		nb = (unsigned int)(-1 * n);
		*aux = '-';
		aux++;
	}
	else
		nb = (unsigned int)n;
	if (nb == 0)
		return (ft_strdup("0"));
	while (nb != 0)
	{
		*aux = (char)(nb % 10 + 48);
		nb = nb / 10;
		aux++;
	}
	*aux = '\0';
	(*buf == '-') ? (ft_strrev(buf + 1)) : (ft_strrev(buf));
	return (ft_strdup(buf));
}
