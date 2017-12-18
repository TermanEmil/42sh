#include <stdlib.h>

void			std_mem_del(void * const mem, size_t const mem_size)
{
	(void)mem_size;
	if (mem != NULL)
		free(mem);
}