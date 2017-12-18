/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:59:40 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 12:19:50 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Appends str2 to *str1, and realocated str1's memory.
**	It uses memory opperations pecause the string, int ft_printf's situation
**	can contain '\0' chars.
*/

void		ft_memappend(char **str1, CHR *str2, int len1, int len2)
{
	char	*result;

	result = ft_strnew(len1 + len2);
	if (result == NULL)
		return ;
	if (*str1 != NULL)
		ft_memcpy((void*)result, (void*)(*str1), len1);
	if (str2 != NULL)
		ft_memcpy((void*)(result + len1), (void*)str2, len2);
	if (*str1 != NULL)
		free(*str1);
	result[len1 + len2] = 0;
	*str1 = result;
}
