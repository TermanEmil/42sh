/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:02 by eterman           #+#    #+#             */
/*   Updated: 2017/05/30 11:13:53 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ustrequ(const t_uchar *s1, const t_uchar *s2)
{
	if (!s1 || !s2)
		return (0);
	return ((ft_memcmp(s1, s2,
		FT_MAX(ft_strlen((const char*)s1), ft_strlen((const char*)s2))) == 0)
		? (1) : (0));
}
