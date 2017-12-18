#include "shell42.h"

/*
** Error processing cursor pos reader.
** I read the position twice, to be sure it's the same in both cases. This trick
** saves tons of bugs...
*/

void	shell_get_cursor_pos(int * const x, int * const y)
{
	int			ret;
	// int			x_aux, y_aux;

	ret = term_get_cursor_pos(g_shinput->term_tty, y, x);
	if (ret == EIO)
		return (shell_get_cursor_pos(x, y));
	if (ret != 0)
		ft_fatal("Failed to get cursor position: %s.", strerror(ret));

	// ret = term_get_cursor_pos(get_shdata()->term_tty, &y_aux, &x_aux);
	// if (ret == EIO)
	// 	return (shell_get_cursor_pos(x, y));
	// if (ret != 0)
	// 	ft_fatal("Failed to get cursor position: %s.", strerror(ret));

	// if (*x != x_aux || *y != y_aux)
	// {
	// 	shell_get_cursor_pos(x, y);
	// }
}
