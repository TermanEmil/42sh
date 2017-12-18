/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:50 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:50 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

void	ft_lstdel(t_list **alst, t_ldel_func *del)
{
	if (*alst)
	{
		ft_lstdel(&(*alst)->next, del);
		ft_lstdelone(alst, del);
	}
}
