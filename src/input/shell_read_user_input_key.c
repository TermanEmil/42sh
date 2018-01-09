#include "eventlib.h"
#include "shinput.h"
#include "termlib.h"

/*
** End of transmision, the same as EOF.
*/

#ifndef EOT
# define EOT 4
#endif

/*
** The first if checks if the 'shell_get_cursor_pos()' didn't interfere with
** the keyboard input.
*/

char const		*shell_read_user_input_key(void)
{
	static t_str	buf = NULL;
	static int		buf_size = 0;
	ssize_t			n;
	t_str			tmp;

	if (buf == NULL)
	{
		buf_size = 4;
		if ((buf = ft_strnew(buf_size)) == NULL)
			ft_err_mem(TRUE);
	}

	n = 0;
	while ((n += read(STDIN_FILENO, buf + n, buf_size - n - 1)) >= buf_size - 1)
	{
		buf_size = buf_size * 2;
		tmp = ft_strnew(buf_size);
		ft_strncpy(tmp, buf, buf_size / 2);
		free(buf);
		buf = tmp;
	}
	
	if (errno)
	{
		if (errno == EINTR)
		{
			errno = 0;
			return NULL;
		}
		else
			ft_err_erno(errno, TRUE);
	}

	buf[n] = 0;
	if (n == 0 || (n == 1 && buf[0] == EOT))
	{
		buf[0] = EOF;
		buf[1] = '\0';
		return buf;
	}
	if (ft_match(buf, "*\033[*;*R*"))
		return (NULL);
	else if (n > 0)
		return (buf);
	else
		return (NULL);
}