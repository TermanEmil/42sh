#include "eventlib.h"

/*
** Listens to all events matching `at_exit*', `memory_frees*' and listens
** to the first occurance of `free_g_events', which frees the g_events.
*/

void	event_exit(int const status)
{
	events_run_iter_matching(g_events, "at_exit*",
		(t_cmp_f*)&std_htab_str_match);
	events_run_iter_matching(g_events, "memory_frees*",
		(t_cmp_f*)&std_htab_str_match);
	events_run_first(g_events, "free_g_events");
	exit(status);
}
