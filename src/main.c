#include "shell42.h"
#include <fcntl.h>
#include "ft_key_codes.h"
#include <time.h>
#include "shellvars.h"

t_shdata		g_shdata;
t_shinput		*g_shinput;
t_current_input	*g_current_in;

int		main(int argc, const char **argv, const char **envp)
{
	init_shell(envp);

	ft_putstr("42sh shell by eterman");
	term_putnewl();
	input_reprint_here(g_current_in);

	while (1)
	{
		shinput_reset_signals(g_shinput);
		shell_read_user_input();
		shinput_process_signals(g_shinput);
	}
	event_exit(0);
}