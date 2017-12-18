/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:05:02 by eterman           #+#    #+#             */
/*   Updated: 2017/02/20 18:17:12 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_errors.h"
#include "eventlib.h"

char const	*g_proj_name;

void		print_proj_name(int fd)
{
	if (g_proj_name)
	{
		ft_putstr_fd(g_proj_name, fd);
		ft_putstr_fd(": ", fd);
	}
}

/*
** Prints a message on stderr
*/

void		ft_err(const char *msg)
{
	ft_putstr_fd(msg, STDERR);
	ft_putchar_fd('\n', STDERR);
}

/*
** After printing a message on stderr, exits.
*/

void		ft_fatal(const char *format, ...)
{
	va_list		ap;
	t_data		*data;

	va_start(ap, format);
	data = sprintf_new_data();
	process_format(format, &ap, data);
	va_end(ap);
	if (data->str)
	{
		write(STDERR_FILENO, data->str, data->printed_chars);
		ft_putnewl();
		free(data->str);
	}
	free(data);
	event_exit(EXIT_FAILURE);
}

/*
** Prints a fatal error about memory alocation.
*/

void		ft_err_mem(int exit_program)
{
	print_proj_name(STDERR);
	ft_err("Cannot allocate memory");
	if (exit_program)
		event_exit(EXIT_FAILURE);
}

/*
** Prints a message, with the project name in front of the message.
*/

int			ft_proj_err(const char *msg, int exit_program)
{
	print_proj_name(STDERR);
	ft_err(msg);
	if (exit_program)
		event_exit(EXIT_FAILURE);
	return (-1);
}
