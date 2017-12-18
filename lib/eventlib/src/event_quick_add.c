#include "eventlib.h"

void	event_quick_add(t_hashtab * const events, char * const key,
			t_handler_f * const handler, void * const data)
{
	event_add(events, key, event_instance_construct(handler, data));
}
