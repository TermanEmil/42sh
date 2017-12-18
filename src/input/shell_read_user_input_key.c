#include "eventlib.h"
#include "shinput.h"
#include "termlib.h"

/*
** The first if checks if the 'shell_get_cursor_pos()' didn't interfere with
** the keyboard input.
*/

char const		*shell_read_user_input_key(void)
{
	static char		buf[4096];
	ssize_t			n;

	n = read(STDIN_FILENO, buf, sizeof(buf) - 1);
	buf[n] = 0;
	if (ft_match(buf, "*\033[*;*R*"))
		return (NULL);
	else if (n > 0)
		return (buf);
	else
		return (NULL);
}