/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variant_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:40:07 by eterman           #+#    #+#             */
/*   Updated: 2016/12/27 17:40:09 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "itoa_base.h"

t_ll		set_variant_value2(
				t_variant *variant,
				t_formats *formats,
				va_list *ap)
{
	t_ll	nb;

	if (ft_strequ(formats->length, "h"))
	{
		variant->type = u_short_int;
		nb = (long long)va_arg(*ap, int);
	}
	else if (ft_strequ(formats->length, "z"))
	{
		variant->type = size_t_val;
		nb = (long long)va_arg(*ap, size_t);
	}
	else if (ft_strequ(formats->length, "j"))
	{
		variant->type = max_val;
		nb = (long long)va_arg(*ap, uintmax_t);
	}
	else
	{
		variant->type = u_integer;
		nb = (long long)va_arg(*ap, int);
	}
	return (nb);
}

/*
** This function sets the type and reads the value from va_list.
** I think there is a big difference between reading an integer from a va_list
** and reading a long long value from it.
** Internets says that int and long int were different once ...
*/

void		set_variant_value(
				t_variant *variant,
				t_formats *formats,
				va_list *ap,
				int base)
{
	long long	nb;

	if (ft_strchr("DU", formats->specifier))
		ft_strcpy(formats->length, "l");
	if (is_long(formats))
	{
		variant->type = u_long_int;
		nb = (long long)va_arg(*ap, long int);
	}
	else if (ft_strequ(formats->length, "ll"))
	{
		variant->type = u_long_long_int;
		nb = (long long)va_arg(*ap, long long);
	}
	else if (ft_strequ(formats->length, "hh"))
	{
		variant->type = u_char_val;
		nb = (long long)va_arg(*ap, int);
	}
	else
		nb = set_variant_value2(variant, formats, ap);
	negative_process(variant, formats, base, &nb);
	variant->val.ull_val = (t_ull)nb;
}
