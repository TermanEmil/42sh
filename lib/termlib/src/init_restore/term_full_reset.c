#include <unistd.h>

void	term_full_reset(void)
{
	write(1, "\033c", 2);
}
