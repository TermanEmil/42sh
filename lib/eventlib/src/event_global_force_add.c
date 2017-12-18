#include "eventlib.h"

/*
** If g_events hasn't been initialized, it will be initilized...
** and a new event will be added to it
*/

void	event_global_force_add(char * const key, t_event_instance const event)
{
	if (g_events == NULL)
		events_init_globals(5);
	event_add(g_events, key, event);
}
