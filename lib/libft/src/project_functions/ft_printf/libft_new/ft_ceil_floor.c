/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ceil_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:17:16 by eterman           #+#    #+#             */
/*   Updated: 2016/12/27 16:49:36 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double		ft_floor(long double n)
{
	t_ll	ni;
	t_ld	rs;

	ni = (t_ll)n;
	rs = ((n < ni) ? (long double)(ni - 1) : (long double)ni);
	rs += FT_SIGN(rs) * MY_ROUND_VAL;
	return (rs);
}

long double		ft_ceil(long double n)
{
	t_ll	ni;
	t_ld	rs;

	ni = (t_ll)n;
	rs = ((n == ni) ? (long double)ni : (long double)(ni + 1));
	rs += FT_SIGN(rs) * MY_ROUND_VAL;
	return (rs);
}
