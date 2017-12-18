/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:20:16 by eterman           #+#    #+#             */
/*   Updated: 2017/01/18 16:52:56 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Replaces target with str in dest.
** Make sure that dest has enough memory.
** I used memmove, to not overwrite.
*/

char	*ft_strreplace(char *dest, char *target, const char *str)
{
	char	*after_target;
	char	*start_of_target;
	size_t	str_len;
	size_t	end_len;

	if (dest == NULL)
		return (NULL);
	if (target == NULL || str == NULL)
		return (dest);
	start_of_target = ft_strstr(dest, target);
	if (start_of_target == NULL)
		return (NULL);
	after_target = start_of_target + ft_strlen(target);
	str_len = ft_strlen(str);
	end_len = ft_strlen(after_target);
	ft_memmove((void*)(start_of_target + str_len), (void*)after_target,
		end_len);
	start_of_target[str_len + end_len] = 0;
	ft_memmove((void*)start_of_target, (void*)str, str_len);
	return (dest);
}
