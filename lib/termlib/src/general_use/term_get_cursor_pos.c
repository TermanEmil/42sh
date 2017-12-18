#include "termlib.h"
#include "eventlib.h"
#include <fcntl.h>

#define RD_EOF -1
#define RD_EIO -2

/*
** http://www.linuxquestions.org/questions/programming-9/
** get-cursor-position-in-c-947833/
*/

/*
** EAGAIN: Resource temporarily unavailable
** EWOULDBLOCK: Operation would block
** EIO: invalid input / output
** It simply does: write(fd, data, bytes), but a guy from the Internet did like
** this, so I thought that I should be more precise about error handling.
*/

static int	cautious_write(int const fd, char * const data,
				size_t const bytes)
{
	char const		*head = data;
	char const		* const tail = data + bytes;
	ssize_t			n;

	while (head < tail)
	{
		n = write(fd, head, (tail - head));
		if (n > 0)
			head += n;
		else if (n != -1)
			return (EIO);
		else if (errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK)
			return (errno);
	}
	return (0);
}

/*
** Checks if buf is formated acrodin to \033[<ROW>;<COL>R
*/

static t_bool	cursor_pos_out_formated(char const *buf)
{
	size_t	len;

	if (buf[0] != '\033' || buf[1] != '[')
		return (FALSE);
	buf += 2;
	len = 0;
	while (*buf >= '0' && *buf <= '9')
	{
		len++;
		buf++;
	}
	if (len > 3 || *buf != ';')
		return (FALSE);
	buf++;
	len = 0;
	while (*buf >= '0' && *buf <= '9')
	{
		len++;
		buf++;
	}
	if (len > 3 || *buf != 'R')
		return (FALSE);
	return (TRUE);
}

/*
** Gets the cursor position of the given tty (teletype, a file descriptor).
** It writes to tty "\033[6n" (a control sequence), after which it is print,
** the cursor coordinates will be inputed in the same tty, in the following
** format: \033[<ROW>;<COL>R where <ROW> and <COL> are the row and column of
** the cursor.
** If any errors occur, the respective errno is returned.
** !!!It is expected that the the given tty is in CANONIAL mode (see termlib.h)
**
** That i is used to stop from infinite loop. U never know what may happen.
*/

int			term_get_cursor_pos(int const tty, int * const row, int * const col)
{
	int		result;
	char	buf[64];
	int		i;

	if (tty == -1)
		return (ENOTTY);
	result = cautious_write(tty, "\033[6n", 4);
	if (result)
		return (result);
	i = 0;
	do
	{
		result = read(tty, buf, sizeof(buf));
		if (result < 0)
			return (term_get_cursor_pos(tty, row, col));
		
		buf[result] = 0;
		if (cursor_pos_out_formated(buf) && ft_match(buf, "\033[*;*R"))
			break;
		else
		{
			i++;
			if (i >= 5)
			{
				tcflush(tty, TCIOFLUSH);
				return (term_get_cursor_pos(tty, row, col));
			}
		}
	} while (1);
	if (row)
		*row = ft_atoi(buf + 2) - 1;
	if (col)
		*col = ft_atoi(ft_strchr(buf, ';') + 1) - 1;
	return (0);
}