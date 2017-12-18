#include "termlib.h"
#include <sys/ioctl.h>

ssize_t	term_get_width(void)
{
	struct winsize	w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
		ft_fatal("ioctl failed to read the screen sizes");
	return (w.ws_col);
}
