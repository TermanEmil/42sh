#include "eventlib.h"

void	events_destruct(t_hashtab ** const events)
{
	del_hashtab(events);
}
