#include "eventlib.h"

t_event_instance	event_instance_construct(t_handler_f * const handler,
						void * const data)
{
	t_event_instance	result;

	result.f = handler;
	result.f_data = data;
	return (result);
}

/*
** An alias of event_instance_construct()
*/

t_event_instance	event_inst_new(t_handler_f * const handler,
						void * const data)
{
	return (event_instance_construct(handler, data));
}