#include "eventlib.h"

t_hashtab	*g_events;

/*
** Initializes the g_events, adding an aouto self free at exit
*/

void		events_init_globals(size_t const starting_nr_of_events)
{
	g_events = events_construct(starting_nr_of_events);
	event_add(g_events, "free_g_events",
		event_instance_construct((t_handler_f*)&events_destruct, &g_events));
}
