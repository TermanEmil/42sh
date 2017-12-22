/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:52 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:52 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

t_list	*ft_lstnew(void const *content, size_t const content_size)
{
	return ft_lstnew_nocpy(
		(content == NULL) ? NULL : ft_memdup(content, content_size),
		content_size);
}
