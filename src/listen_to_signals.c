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

/*
** SIG_DFL stands for "do the default thing".
** The thing with ioctl here: sends the suspend character to terminal.
*/

static void	handle_suspend_and_cont(int signum)
{
	(void)signum;
	event_exit(0);
}

static void	handle_window_resize(int signum)
{
	(void)signum;
}

/*
** Term restore happens at exit
*/

static void	handle_signal(int signum)
{
	(void)signum;
}

static void	handle_sigint(int signum)
{
	(void)signum;
	g_shinput->signaled_sigint = TRUE;
}

static void	set_sigint(void)
{
	struct sigaction	handler_data;

	ft_bzero(&handler_data, sizeof(handler_data));
	handler_data.sa_handler = &handle_sigint;
	if (sigaction(SIGINT, &handler_data, NULL) == -1)
		ft_proj_err("can't listen to SIGINT", 1);
}

void		listen_to_signals(void)
{
	int		i;

	if (signal(SIGTSTP, &handle_suspend_and_cont) == SIG_ERR)
		ft_proj_err("can't listen to SIGTSTP", 1);
	if (signal(SIGCONT, &handle_suspend_and_cont) == SIG_ERR)
		ft_proj_err("can't listen to SIGCONT", 1);
	if (signal(SIGWINCH, &handle_window_resize) == SIG_ERR)
		ft_proj_err("can't listen to SIGWINCH", 1);
	set_sigint();
	
	i = 0;
	while (i < 32)
	{
		if (i != SIGKILL && i != SIGSTOP && i != SIGCHLD && i != SIGCONT &&
			i != SIGURG && i != SIGIO && i != SIGWINCH && i != SIGTSTP &&
			i != SIGINT)
			signal(i, &handle_signal);
		i++;
	}
}
