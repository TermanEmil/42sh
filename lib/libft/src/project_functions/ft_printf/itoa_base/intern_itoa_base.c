/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_itoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:17:46 by eterman           #+#    #+#             */
/*   Updated: 2016/11/30 12:49:06 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "itoa_base.h"

/*
** it's recursive itoa
*/

static void	rec_itoa(t_variant *variant, int base, char *buff, int (*f)(int))
{
	int		i;
	int		less_than_base;

	var_inf(&i, &less_than_base, base, variant);
	if (less_than_base)
	{
		*buff = f(BASE[i]);
		buff[1] = '\0';
	}
	else
	{
		*buff = f(BASE[i]);
		rec_itoa(variant, base, buff + 1, f);
	}
}

/*
** if (upper) then it will be X else x
*/

static char	*variant_itoa(t_variant *variant, int base, int upper)
{
	char		static_buff[200];
	char		*buff;

	buff = static_buff;
	if (base == 10 && variant->is_negative)
	{
		*buff = '-';
		buff++;
	}
	rec_itoa(variant, base, buff, ((upper) ? (ft_toupper) : (ft_tolower)));
	ft_strrev(buff);
	return (ft_strdup(static_buff));
}

/*
** The itoa_base function which takes a va_list parameter.
*/

char		*va_arg_itoa(va_list *ap, int base, int upper, t_formats *formats)
{
	t_variant	*variant;
	char		*result;

	variant = (t_variant*)malloc(sizeof(t_variant));
	variant->is_negative = 0;
	set_variant_value(variant, formats, ap, base);
	result = variant_itoa(variant, base, upper);
	free(variant);
	return (result);
}
