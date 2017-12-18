/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 10:04:05 by eterman           #+#    #+#             */
/*   Updated: 2016/11/07 10:35:05 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Generally speaking, this functions reads a line from a given file.
** It read by BUFF_SIZE chars (see get_next_line.h).
** It uses a static variable to store data. (I use lists for multiple file
** reading).
*/

/*
** Realocate the memory for buffer (stock), adding to it the new_str
*/

int			ft_addstr(char **buffer, char *new_str, size_t size)
{
	char	*aux;

	if (*buffer == NULL)
		return ((*buffer = ft_strdup(new_str)) == NULL);
	aux = ft_strnew(ft_strlen(*buffer) + size);
	ft_strcpy(aux, *buffer);
	ft_strcat(aux, new_str);
	free(*buffer);
	*buffer = aux;
	return (0);
}

/*
** Removes the stock indexed with fd from head 'list'
*/

int			remove_stock(t_fd_stock **head, int const fd)
{
	t_fd_stock		*prev;
	t_fd_stock		*aux;

	prev = NULL;
	aux = *head;
	while ((aux)->fd != fd)
	{
		prev = aux;
		aux = (aux)->next;
	}
	free((aux)->stock);
	if (*head == aux)
		*head = ((*head)->next);
	else
		prev->next = (aux)->next;
	free(aux);
	return (0);
}

/*
** Gets the address of the stock for specified fd
** It searches through all the current elements
** If the head (or current cellule is null) creates a new cell
*/

char		**get_stock(t_fd_stock **head, int const fd)
{
	if (*head == NULL)
	{
		*head = (t_fd_stock*)malloc(sizeof(t_fd_stock));
		(*head)->stock = ft_strnew(1);
		(*head)->fd = fd;
		(*head)->next = NULL;
		return (&((*head)->stock));
	}
	if ((*head)->fd != fd)
		return (get_stock(&((*head)->next), fd));
	return (&((*head)->stock));
}

/*
** I've just ran out of lines ...
*/

int			form_result(char **stock, char **line, t_fd_stock **head, int fd)
{
	char	*new_line;
	int		stock_len;
	char	*aux;

	if (ft_strlen(*stock) == 0)
		return (remove_stock(head, fd));
	new_line = ft_strchrnul(*stock, '\n');
	stock_len = ft_strlen(new_line);
	*new_line = '\0';
	if ((*line = ft_strdup(*stock)) == NULL)
		return (-1);
	if (stock_len == 0)
	{
		free(*stock);
		*stock = ft_strnew(1);
	}
	else
	{
		aux = ft_strdup(new_line + 1);
		free(*stock);
		*stock = aux;
	}
	return (1);
}

/*
** Returns -1 ENOMEM
** Returns -2 if couldn't read from fd
*/

int			get_next_line(int const fd, char **line)
{
	static t_fd_stock	*head = NULL;
	char				**stock;
	char				*buffer;
	int					ret;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 ||
		(buffer = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	stock = get_stock(&head, fd);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (ft_addstr(stock, buffer, ret))
		{
			free(buffer);
			return (-1);
		}
		if (ft_strchr(*stock, '\n'))
			break ;
	}
	free(buffer);
	if (ret < 0)
		return (-2);
	return (form_result(stock, line, &head, fd));
}
