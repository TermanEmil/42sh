/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrm_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:40:03 by eterman           #+#    #+#             */
/*   Updated: 2017/02/24 18:40:03 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Removes n chars from index in str. Be sure to give a valid
** string, no checking is performed.
*/

void	ft_strrm_n(char *str, size_t index, size_t n)
{
	size_t	end_len;
	
	end_len = ft_strlen(str + index + n);
	ft_memmove(str + index, str + index + n, end_len);
	ft_bzero(str + index + end_len, n);
}
