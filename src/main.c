#include "shell42.h"
#include <fcntl.h>
#include <time.h>
#include "shellvars.h"
#include <regex.h>
#include <stdio.h>

t_shdata		g_shdata;
t_shinput		*g_shinput;
t_current_input	*g_current_in;

int		main(int argc, const char **argv, const char **envp)
{
	init_shell(envp);

	(void)argv;
	(void)argc;
	if (g_shdata.is_term)
	{
		ft_putstr("42sh shell by eterman");	
		term_putnewl();
		input_reprint_here(g_current_in);
	}

	while (1)
	{
		shinput_reset_signals(g_shinput);
		if (g_shdata.sub_sh != NULL)
		{
			uinput_mince_raw(g_shdata.sub_sh->raw_cmd);
			event_exit(0);
		}
		else
			shell_read_user_input();
		shinput_process_signals(g_shinput);
	}

	event_exit(0);
}
