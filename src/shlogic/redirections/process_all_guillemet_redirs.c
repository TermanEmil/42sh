#include "shell_redirs_.h"
#include "regex_tools.h"

#define REG_ALL_3_REDIRS_	"("							\
								REG_TO_FILE_REDIR "|"	\
								REG_TO_FD_REDIR "|"		\
								REG_CLOSE_FD			\
							")"							\

void			process_all_guillemet_redirs(
					t_pipe_env *pipe_env,
					t_cmd_env *cmd_env)
{
	t_str				word_str;
	const t_lst_words	*words;

	words = LCONT(cmd_env->pipe_queue_iter, t_lst_words*);
	for (; words; LTONEXT(words))
	{
		word_str = word_to_str(LCONT(words, t_lst_inkey*));
		if (word_str == NULL)
			ft_err_mem(TRUE);

		if (regex_mini_match(REG_ALL_3_REDIRS_, word_str))
			process_guillemet_redir(pipe_env, cmd_env, word_str, words->next);
		
		free(word_str);
	}
}
