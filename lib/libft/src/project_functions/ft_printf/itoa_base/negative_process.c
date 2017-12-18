/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 20:29:34 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 20:29:36 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "itoa_base.h"

void		negative_process(
				t_variant *variant,
				t_formats *formats,
				int base,
				long long *nb)
{
	if (base == 10 && ft_toupper(formats->specifier) != 'U')
	{
		if ((variant->type == u_integer && (int)(*nb) < 0) ||
			(variant->type == u_long_int && (long int)(*nb) < 0) ||
			(variant->type == u_long_long_int && (long long int)(*nb) < 0) ||
			(variant->type == u_short_int && (short)(*nb) < 0) ||
			(variant->type == u_char_val && (char)(*nb) < 0) ||
			(variant->type == max_val && (intmax_t)(*nb) < 0) ||
			(variant->type == size_t_val && (long long)(*nb) < 0))
		{
			*nb = -*nb;
			variant->is_negative = 1;
		}
	}
}
