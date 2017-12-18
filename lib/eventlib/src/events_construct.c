#include "eventlib.h"

t_hashtab	*events_construct(size_t const len)
{
	return  (new_hashtab(len, NULL, (t_del_mem_f*)&event_instance_destruct));
}
