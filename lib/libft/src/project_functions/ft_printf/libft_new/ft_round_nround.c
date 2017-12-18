/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_nround.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:32:03 by eterman           #+#    #+#             */
/*   Updated: 2016/12/27 16:51:13 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_ull	ft_ten_pow(int power)
{
	t_ull	rs;

	rs = 1;
	if (power > 18)
		power = 18;
	while (power > 0)
	{
		rs *= 10;
		power--;
	}
	return (rs);
}

long double		ft_round(long double n)
{
	long double	val;

	val = (FT_ABS(n) + MY_ROUND_VAL);
	if (val > (ft_floor(val) + 0.5 + 0.00000001))
		val = ft_ceil(val);
	else
		val = ft_floor(val);
	return (FT_SIGN(n) * val);
}

long double		ft_nround(long double n, int precision)
{
	t_ll		power_val;

	power_val = ft_ten_pow(precision);
	return (ft_round(n * power_val) / power_val);
}
