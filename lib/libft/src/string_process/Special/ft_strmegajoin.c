/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmegajoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:06:21 by eterman           #+#    #+#             */
/*   Updated: 2017/01/15 20:37:51 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	count_len(va_list *ap, int argc)
{
	char	*str;
	int		result;

	result = 0;
	while (argc)
	{
		argc--;
		str = (char*)va_arg(*ap, char*);
		if (str != NULL)
			result += ft_strlen(str);
	}
	return (result);
}

char		*ft_strmegajoin(int argc, ...)
{
	char			*result;
	va_list			ap;
	char			*str;

	va_start(ap, argc);
	result = (char*)malloc(sizeof(char) * count_len(&ap, argc) + 1);
	va_end(ap);
	if (result == NULL)
		return (NULL);
	*result = 0;
	va_start(ap, argc);
	while (argc)
	{
		argc--;
		if ((str = (char*)va_arg(ap, char*)) != NULL)
			ft_strcat(result, str);
	}
	va_end(ap);
	return (result);
}
