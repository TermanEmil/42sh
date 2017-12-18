#include "termlib.h"
#include <fcntl.h>

/*
** Returns an OPENED file descriptor of the current terminal file descriptor.
** Returns -1 on error.
** ttyname(STDIN_FILENO) == ttyname(STDOUT_FILENO) == ttyname(STDERR_FILENO).
**
** http://www.linuxquestions.org/questions/programming-9/
** get-cursor-position-in-c-947833/
*/

int		term_get_current_tty(void)
{
	char const 	*dev;
	int			fd;

	dev = ttyname(STDIN_FILENO);
	if (!dev)
		dev = ttyname(STDOUT_FILENO);
	if (!dev)
		dev = ttyname(STDERR_FILENO);
	if (!dev)
	{
		errno = ENOTTY;
		return (-1);
	}
	do
	{
		fd = open(dev, O_RDWR | O_NOCTTY);
	} while (fd == -1 && errno == EINTR);
	if (fd == -1)
		return (-1);
	return (fd);
}
