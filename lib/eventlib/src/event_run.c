#include "eventlib.h"

void		event_run(t_event_instance const *event)
{
	if (event)
		event->f(event->f_data);
}
