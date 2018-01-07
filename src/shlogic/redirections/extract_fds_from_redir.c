#include "shell_redirs_.h"
#include "regex_tools.h"

void		extract_fds_from_redir(t_rostr redir_str, int *fd1, int *fd2)
{
	t_str	buf;
	t_rostr	start_of_redir;
	t_rostr	start_of_ampersand;

	start_of_redir = ft_strnchr(redir_str, "><");
	if (start_of_redir == redir_str)
		*fd1 = -1;
	else
		*fd1 = ft_atoi(redir_str);

	start_of_ampersand = ft_strchr(start_of_redir, '&');
	if (start_of_ampersand == NULL)
		*fd2 = -1;
	else
	{
		buf = regex_get_match("[0-9]+", start_of_ampersand);

		if (buf == NULL)
			*fd2 = -1;
		else
		{
			*fd2 = ft_atoi(buf);
			free(buf);
		}
	}
}
