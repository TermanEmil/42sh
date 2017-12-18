/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_new_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 14:23:35 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 14:56:35 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_data			*sprintf_new_data(void)
{
	t_data		*data;

	data = (t_data*)malloc(sizeof(t_data));
	data->color_count = 1;
	data->printed_chars = 0;
	data->color_should_clean = 0;
	data->str = NULL;
	data->not_counted_chars = 0;
	return (data);
}
