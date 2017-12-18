/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_of_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:44:52 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 12:16:22 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the index of the word in string.
** Ex: ft_index_of_word("green", "black red green yellow blue") == 2
*/

int			ft_index_of_word(char *word, char *str, char *delims)
{
	int		len;
	int		i;
	int		index;

	i = 0;
	index = -1;
	while (str[i])
	{
		while (ft_strchr(delims, str[i]))
			i++;
		if (str[i] == 0)
			break ;
		index++;
		len = 0;
		while (str[i + len] && !ft_strchr(delims, str[i + len]))
			len++;
		if ((int)ft_strlen(word) == len && ft_strnequ(word, &(str[i]), len))
			return (index);
		i += len;
		if (str[i] == 0)
			break ;
	}
	return (-1);
}
