#include "eventlib.h"

void	event_instance_destruct(t_event_instance * const instance)
{
	if (instance)
		free(instance);
}
