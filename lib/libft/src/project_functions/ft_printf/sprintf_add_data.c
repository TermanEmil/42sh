/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_add_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 12:05:11 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 12:30:01 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		sprintf_add_data(t_data *data, CHR *str2, int len2)
{
	ft_memappend(&(data->str), str2, data->printed_chars, len2);
	data->printed_chars += len2;
}
