/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 12:00:59 by eterman           #+#    #+#             */
/*   Updated: 2017/02/19 20:36:14 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Compare strings like: 'file.txt' and '*.txt' == 1
*/

int		ft_match(char const *s1, char const *s2)
{
	if (*s1 != '\0' && *s2 == '*')
		return (ft_match(s1 + 1, s2) || ft_match(s1, s2 + 1));
	if (*s1 == '\0' && *s2 == '*')
		return (ft_match(s1, s2 + 1));
	if (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
		return (ft_match(s1 + 1, s2 + 1));
	if (*s1 == *s2 && *s1 == '\0' && *s2 == '\0')
		return (1);
	return (0);
}
