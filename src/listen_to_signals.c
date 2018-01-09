/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_to_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:57:33 by eterman           #+#    #+#             */
/*   Updated: 2017/05/15 11:01:57 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <signal.h>
#include "shell42.h"
#include "eventlib.h"
#include "ft_signals.h"

static void	handle_sigint(int signum)
{
	(void)signum;
	g_shinput->signaled_sigint = TRUE;
}

void		listen_to_signals(void)
{
	ft_sigaction(SIGINT, &handle_sigint);
}
