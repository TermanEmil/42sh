/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:51 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:51 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

int		ft_lstlen(t_list const * head)
{
	int		result;

	result = 0;
	while (head)
	{
		result++;
		head = head->next;
	}
	return (result);
}
