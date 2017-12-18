/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_n_specifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 15:00:09 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 15:32:49 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			process_n_specifier(va_list *ap, t_data *data)
{
	int		*n;

	n = (int*)va_arg(*ap, int*);
	if (n)
		*n = data->printed_chars - data->not_counted_chars;
}
