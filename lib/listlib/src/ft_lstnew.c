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
	t_list	*result;

	result = (t_list*)malloc(sizeof(t_list));
	if (result == NULL)
		return (NULL);
	result->next = NULL;
	result->prev = NULL;
	if (content == NULL)
	{
		result->content = NULL;
		result->content_size = 0;
	}
	else
	{
		result->content = ft_memdup(content, content_size);
		result->content_size = content_size;
	}
	return (result);
}
