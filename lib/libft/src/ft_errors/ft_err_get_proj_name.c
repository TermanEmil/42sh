/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_get_proj_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 18:08:16 by eterman           #+#    #+#             */
/*   Updated: 2017/02/20 18:24:27 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_errors.h"

void		ft_err_init_proj_name(char const *proj_name)
{
	g_proj_name = proj_name;
}
