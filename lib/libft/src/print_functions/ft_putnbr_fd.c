/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:57 by eterman           #+#    #+#             */
/*   Updated: 2016/10/24 18:56:16 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec_putnbr(unsigned int nb, int fd)
{
	if (nb <= 9)
		ft_putchar_fd(nb + 48, fd);
	else
	{
		rec_putnbr(nb / 10, fd);
		ft_putchar_fd(nb % 10 + 48, fd);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	int				k;

	if (n < 0)
		k = -1;
	else
		k = 1;
	nb = (unsigned int)(n * k);
	if (k == -1)
		ft_putchar_fd('-', fd);
	rec_putnbr(nb, fd);
}
