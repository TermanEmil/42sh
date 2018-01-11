#include "shell42.h"

static void				shell_process_ctrl_d()
{
	if (ft_lstlen(g_current_in->input->keys) == 0)
	{
		IF_TERM(ft_putstr("exit"));
		IF_TERM(term_putnewl());
		event_exit(0);
	}
}

/*
** Still has plenty of bugs...
*/

void					shell_read_user_input(void)
{
	char const	*raw_in = shell_read_user_input_key();

	if (raw_in == NULL)
		return;
	if (raw_in[0] == EOF)
		shell_process_ctrl_d();

	uinput_mince_raw(raw_in);
}
