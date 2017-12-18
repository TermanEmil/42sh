#include "libft.h"

void	term_save_cursor_pos(void)
{
	ft_putstr("\0337");
}

void	term_restore_cursor_pos(void)
{
	ft_putstr("\0338");	
}
