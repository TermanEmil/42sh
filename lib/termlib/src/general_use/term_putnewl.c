#include "termlib.h"

void	term_putnewl(void)
{
	ft_putnewl();
	term_move_cursor_to_left_most();
}
