/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 22:40:39 by eterman           #+#    #+#             */
/*   Updated: 2016/12/25 23:00:39 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define FLAGS		"# -+0"

int			prev_is_point(char *src, int i)
{
	if (i == 0)
		return (0);
	if (src[i - 1] == '.')
		return (1);
	return (0);
}

int			has_zero_flag(char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		if (src[i] == '0' && !prev_is_point(src, i))
			return (1);
		while (ft_isdigit(src[i]))
			i++;
		if (src[i])
			i++;
	}
	return (0);
}

void		extract_flags(char *src, t_formats *formats)
{
	int		i;
	int		len;
	int		count;

	formats->flags[0] = 0;
	len = ft_strlen(FLAGS);
	i = 0;
	count = 0;
	while (i < len - 1)
	{
		if (ft_strchr(src, FLAGS[i]))
		{
			formats->flags[count] = FLAGS[i];
			count++;
		}
		i++;
	}
	if (has_zero_flag(src))
		formats->flags[count] = '0';
}
