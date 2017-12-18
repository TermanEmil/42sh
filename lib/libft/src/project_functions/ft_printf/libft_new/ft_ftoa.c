/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:13:12 by eterman           #+#    #+#             */
/*   Updated: 2016/12/27 15:34:02 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			process_naninf(long double n, char *buff)
{
	if (ft_isnan(n))
	{
		ft_strcpy(buff, "nan");
		return (1);
	}
	else if (ft_isinf(n) == -1)
	{
		ft_strcpy(buff, "-inf");
		return (1);
	}
	else if (ft_isinf(n) == 1)
	{
		ft_strcpy(buff, "inf");
		return (1);
	}
	else
		return (0);
}

char		*ft_ftoa(long double n, int precision)
{
	char	result[15 * sizeof(long double)];
	int		i;

	if (process_naninf(n, result))
		return (ft_strdup(result));
	n = ft_nround(n + FT_SIGN(n) * MY_ROUND_VAL, precision);
	if ((long long)n == 0 && n < 0 && precision)
		ft_strcpy(result, "-0");
	else
		ft_bufitoa((long long)n, result);
	if (precision > 0)
		ft_strcat(result, ".");
	n = FT_ABS(n - (t_ll)n);
	i = ft_strlen(result);
	while (precision)
	{
		n *= 10;
		if (precision == 1)
			n = ft_round(n);
		result[i++] = BASE[(t_ll)n % 10];
		precision--;
	}
	result[i] = 0;
	return (ft_strdup(result));
}
