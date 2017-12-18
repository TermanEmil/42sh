/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:33:57 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 11:59:17 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_textcmd(int index)
{
	static char	buff[20];

	ft_strcpy(buff, "\x1B[");
	ft_bufitoa(index, buff + ft_strlen(buff));
	ft_strcat(buff, "m");
	return (buff);
}
