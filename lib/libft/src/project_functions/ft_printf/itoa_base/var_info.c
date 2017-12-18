/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:42:36 by eterman           #+#    #+#             */
/*   Updated: 2016/12/27 17:42:37 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "itoa_base.h"

static void	var_inf2(int *i, int *less_than_base, int base, t_variant *variant)
{
	if (variant->type == u_short_int)
	{
		LESS_THAN_BASE(h_val);
		SET_INDEX(h_val);
		DIV_VAL(h_val);
	}
	else if (variant->type == u_char_val)
	{
		LESS_THAN_BASE(uc_val);
		SET_INDEX(uc_val);
		DIV_VAL(uc_val);
	}
	else if (variant->type == size_t_val)
	{
		LESS_THAN_BASE(st_val);
		SET_INDEX(st_val);
		DIV_VAL(st_val);
	}
	else if (variant->type == max_val)
	{
		LESS_THAN_BASE(st_val);
		SET_INDEX(st_val);
		DIV_VAL(st_val);
	}
}

/*
** This function uses VAR_INFO definition to avoid the repetion of code.
** It updates the information:
** less_than_base = val < base;
** i = val % base;
** val /= base;
*/

void		var_inf(int *i, int *less_than_base, int base, t_variant *variant)
{
	if (variant->type == u_integer)
	{
		LESS_THAN_BASE(u_val);
		SET_INDEX(u_val);
		DIV_VAL(u_val);
	}
	else if (variant->type == u_long_int)
	{
		LESS_THAN_BASE(ul_val);
		SET_INDEX(ul_val);
		DIV_VAL(ul_val);
	}
	else if (variant->type == u_long_long_int)
	{
		LESS_THAN_BASE(ull_val);
		SET_INDEX(ull_val);
		DIV_VAL(ull_val);
	}
	else
		var_inf2(i, less_than_base, base, variant);
}
