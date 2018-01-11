#include "shell_redirs_.h"
#include "regex_tools.h"

#define REG_ANY_FILE_REDIR_	"("							\
								REG_TO_FILE_REDIR "|"	\
								REG_TO_FD_REDIR			\
							")"							\

void		process_guillemet_redir(
					t_pipe_env *pipe_env,
					t_cmd_env *cmd_env,
					t_rostr redir_str,
					t_lst_words *next_words)
{
	t_redir_env		redir_env;

	redir_env = new_redir_env(redir_str, next_words);

	if (regex_mini_match(REG_CLOSE_FD, redir_str))
		process_guillemet_close_fd(cmd_env, &redir_env);
	else if (regex_mini_match(REG_ANY_FILE_REDIR_, redir_str))
		process_guillemet_redir_to_from_file(pipe_env, cmd_env, &redir_env);
	else
	{
		cmd_env->success = FALSE;
		ft_error(FALSE, "%s: %s: invalid redirection\n",
			g_proj_name, redir_str);
		return;
	}

	del_redir_env(&redir_env);
}
