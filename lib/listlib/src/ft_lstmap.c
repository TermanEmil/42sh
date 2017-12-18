/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:52 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:52 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;

	if (!lst)
		return (NULL);
	result = NULL;
	while (lst)
	{
		ft_lstadd(&result, f(lst));
		lst = lst->next;
	}
	return (result);
}
