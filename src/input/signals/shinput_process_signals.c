#include "shinput.h"

void	shinput_process_signals(t_shinput * const shinput)
{
	current_in_handle_sigint(shinput);
}
