/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:29:25 by eterman           #+#    #+#             */
/*   Updated: 2016/12/27 17:29:26 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function realocates the memory of str.
** str can have be bigger thant its content.
*/

char			*ft_strrealoc(char **str)
{
	char		*aux;

	if (*str != NULL)
	{
		aux = ft_strdup(*str);
		free(*str);
		*str = aux;
		return (*str);
	}
	return (NULL);
}
