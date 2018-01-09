#include "shell42.h"
#include "shinput.h"


void	read_process_non_term_input()
{
	t_rostr	raw_in;

	raw_in = shell_read_user_input_key();
	if (raw_in == NULL)
		return;

	// uinput_mince_raw(raw_in);
}
