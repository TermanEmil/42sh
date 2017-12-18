/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:39:07 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:39:07 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function to reverse a string
*/

char	*ft_strrev(char *str)
{
	unsigned int	len;
	unsigned int	i;
	char			temp;
	int				int_temp;

	len = ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		temp = str[i];
		int_temp = len - i - 1;
		str[i] = str[int_temp];
		str[int_temp] = temp;
		i++;
	}
	return (str);
}
