/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:38:51 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 11:38:51 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

void	ft_lstdelone(t_list ** const alst, void (* const del)(void*, size_t))
{
	if (del)
		del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
