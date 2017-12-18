/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:01 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:01 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*rs;

	rs = (char*)malloc(ft_strlen(s) + 1);
	if (rs == NULL)
		return (NULL);
	ft_strcpy(rs, s);
	return (rs);
}
