/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort_merge.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 17:15:46 by eterman           #+#    #+#             */
/*   Updated: 2017/01/03 17:46:56 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

/*
** Source:
**		http://www.geeksforgeeks.org/merge-sort-for-linked-list/
** if (f(a->content, b->content) > 0)
*/

static void		front_back_split(
					t_list *source,
					t_list **front_ref,
					t_list **back_ref)
{
	t_list	*fast;
	t_list	*slow;

	if (source == NULL || source->next == NULL)
	{
		*front_ref = source;
		*back_ref = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front_ref = source;
		*back_ref = slow->next;
		slow->next = NULL;
	}
}

static t_list	*sorted_merge(t_list *a, t_list *b, int (*f)(void*, void*))
{
	t_list	*result;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (f(a->content, b->content) > 0)
	{
		result = a;
		result->next = sorted_merge(a->next, b, f);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next, f);
	}
	return (result);
}

void			ft_lst_merge_sort(t_list **head_ref, int (*f)(void*, void*))
{
	t_list	*head;
	t_list	*a;
	t_list	*b;

	head = *head_ref;
	if (head == NULL || head->next == NULL)
		return ;
	front_back_split(head, &a, &b);
	ft_lst_merge_sort(&a, f);
	ft_lst_merge_sort(&b, f);
	*head_ref = sorted_merge(a, b, f);
}
