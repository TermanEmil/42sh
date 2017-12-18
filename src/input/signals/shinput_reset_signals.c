#include "shinput.h"

void	shinput_reset_signals(t_shinput * const shinput)
{
	shinput->signaled_sigint = FALSE;
}
