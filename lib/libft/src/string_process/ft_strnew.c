/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:06 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:06 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*result;

	result = (char*)ft_memalloc(size + 1);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, size + 1);
	return (result);
}
