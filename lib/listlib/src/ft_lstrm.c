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

static void		rec_rm(
					t_list **head,
					t_list *target,
					t_list *prev,
					void (*del)(void*, size_t))
{
	t_list	*tmp;

	if (*head == NULL)
		return;
	if (*head == target)
	{
		tmp = *head;
		if (prev == NULL)
		{
			LTONEXT(*head);
			LPREV(*head) = NULL;
		}
		else
		{
			if (LNEXT(*head))
				LPREV(LNEXT(*head)) = prev;
			prev->next = LNEXT(*head);
		}
		ft_lstdelone(&tmp, del);
	}
	else
		rec_rm(&LNEXT(*head), target, *head, del);
}

void			ft_lstrm(t_list **head,
					t_list *target, void (*del)(void*, size_t))
{
	rec_rm(head, target, NULL, del);
}
