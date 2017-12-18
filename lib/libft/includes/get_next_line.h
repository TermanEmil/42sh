/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 10:07:45 by eterman           #+#    #+#             */
/*   Updated: 2016/11/07 10:35:15 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE 128

typedef struct			s_fd_stock
{
	char				*stock;
	int					fd;
	struct s_fd_stock	*next;
}						t_fd_stock;

int						get_next_line(int const fd, char **line);

#endif
