/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:20:49 by eterman           #+#    #+#             */
/*   Updated: 2017/02/18 17:20:49 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

void			ft_lstrm(t_list **head,
					t_list *target, void (*del)(void*, size_t))
{
	t_list	*element;

	element = ft_lst_detach(head, target);
	if (element)
		ft_lstdelone(&element, del);
}
