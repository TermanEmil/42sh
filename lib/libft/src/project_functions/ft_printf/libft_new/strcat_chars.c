/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 20:24:59 by eterman           #+#    #+#             */
/*   Updated: 2016/12/26 20:25:04 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	strcat_chars(char *str, int count, char c)
{
	while (*str)
		str++;
	while (count)
	{
		*str = c;
		str++;
		count--;
	}
}
