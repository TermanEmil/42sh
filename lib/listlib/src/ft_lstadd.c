/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:50 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 16:28:28 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

/*
** Modified !
** Normally, list.add(element) adds the element at the end.
*/

void	ft_lstadd(t_list **head, t_list *new)
{
	if (*head == NULL)
		*head = new;
	else
	{
		if (LNEXT(*head) == NULL)
			new->prev = *head;
		ft_lstadd(&(LNEXT(*head)), new);
	}
}
