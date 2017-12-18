/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnaninf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:18:48 by eterman           #+#    #+#             */
/*   Updated: 2016/12/27 16:47:48 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isinf(double x)
{
	unsigned long long	*val;

	val = (unsigned long long *)&x;
	if (*val == 0x7ff0000000000000)
		return (1);
	else if (*val == 0xfff0000000000000)
		return (-1);
	return (0);
}

int		ft_isnan(double x)
{
	return (x != x);
}
