#include "shell_redirs_.h"
#include "regex_tools.h"

t_redir_env	new_redir_env(t_rostr redir, t_lst_words *next_words)
{
	t_redir_env	result;

	result.redir = redir;
	extract_fds_from_redir(redir, &result.left_fd, &result.right_fd);
	result.redir_type = regex_get_match("[><]+", redir);
	
	if (next_words == NULL)
		result.next_word_str = NULL;
	else
	{
		result.next_word_str = word_to_argv(LCONT(next_words, t_lst_inkey*));
		if (result.next_word_str == NULL)
			ft_err_mem(TRUE);
	}
	return result;
}
