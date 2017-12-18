/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 09:00:30 by eterman           #+#    #+#             */
/*   Updated: 2017/02/21 11:33:59 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_hex_mem(unsigned char *c_ptr, size_t size, int base,
				size_t *max)
{
	size_t		i;
	size_t		chars_printed;
	char		*s;
	
	chars_printed = 0;
	i = 0;
	while (i < size)
	{
		if (base == 2)
			ft_sprintf(&s, "%0.8b", c_ptr[i]);
		else if (base == 8)
			ft_sprintf(&s, "%0.3o", c_ptr[i]);
		else if (base == 10)
			ft_sprintf(&s, "%0.2d", c_ptr[i]);
		else
			ft_sprintf(&s, "%0.2x", c_ptr[i]);
		ft_putstr(s);
		chars_printed += ft_strlen(s);
		i++;
		ft_putchar(' ');
		chars_printed++;
		free(s);
	}
	if (*max == 0)
		*max = chars_printed;
	else
		print_n_times(" ", *max - chars_printed, 1);
}

static void	print_visible_mem(unsigned char *c_ptr, size_t size)
{
	size_t		i;
	
	i = 0;
	while (i < size)
	{
		if (ft_isprint(c_ptr[i]))
			ft_putchar(c_ptr[i]);
		else
			ft_putchar('.');
		i++;
	}
	ft_putchar('\n');
}

void		ft_print_mem(void const *ptr, size_t size, int base)
{
	unsigned char	*c_ptr;
	size_t		max;
	
	if (!ptr)
		return ;
	c_ptr = (unsigned char*)ptr;
	max = 0;
	while (size)
	{
		print_hex_mem(c_ptr, FT_MIN(size, 8), base, &max);
		print_visible_mem(c_ptr, FT_MIN(size, 8));
		if (size < 8)
			break ;
		size -= 8;
		c_ptr += 8;
	}
}
