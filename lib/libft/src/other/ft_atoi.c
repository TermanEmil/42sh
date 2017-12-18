/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:46 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:40:23 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_jump_inviz jumps over invisible part of string
*/

static void	ft_jump_inviz(const char **str)
{
	while (**str && ft_strchr("\t\r\f\v\n ", **str))
		*str += 1;
}

/*
** ft_first_char_sign gets the sign of the first
** string's char and jumps over it if there was
** found one
*/

static int	ft_first_char_sign(const char **str)
{
	if (ft_strchr("-+", **str))
	{
		*str += 1;
		if (*(*str - 1) == '-')
			return (-1);
	}
	return (1);
}

int			ft_atoi(const char *str)
{
	int		sign;
	int		result;

	ft_jump_inviz(&str);
	sign = ft_first_char_sign(&str);
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}
