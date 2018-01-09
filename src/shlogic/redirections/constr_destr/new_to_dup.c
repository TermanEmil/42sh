#include "shell_redirs_.h"

t_to_dup	new_to_dup(int fd, int default_fd, t_bool to_close)
{
	t_to_dup	result;

	result.fd = fd;
	result.default_fd = default_fd;
	result.to_close = to_close;
	return result;
}
