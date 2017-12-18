/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 15:45:22 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 15:55:04 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

void	ft_lst_push_front(t_list **first, t_list *new)
{
	if (*first)
	{
		new->next = *first;
		(*first)->prev = new;
	}
	*first = new;
}
