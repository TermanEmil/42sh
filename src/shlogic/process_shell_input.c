#include "shlogic.h"
#include "shell_redirs_.h"
#include "shell42.h"
#include <signal.h>
#include <sys/types.h>

void	process_cmds(
			t_grps_wrds *cmd_queue,
			t_shvars *shvars,
			const t_hashtab *built_in_cmds)
{
	t_grps_wrds	*pipe_queue;
	t_lst_words	*words;
	int			ret;

	for (; cmd_queue; LTONEXT(cmd_queue))
	{
		words = LCONT(cmd_queue, t_lst_words*);
		if (words_match_single(words, "^;$"))
			continue;

		pipe_queue = group_words_by_delim(words, PIPE_DELIM);
		ret = process_pipe_queue(
			new_pipe_env(pipe_queue, built_in_cmds, shvars));
		del_groups_of_words(pipe_queue);
		if (ret == -2)
		{
			break;
		}
	}
}

void	process_shell_input(
			t_lst_inkey *keys,
			t_shvars *shvars,
			const t_hashtab *built_in_cmds)
{
	t_lst_words	*words;
	t_grps_wrds	*cmd_queue;

	words = extract_words_from_keys(keys);
	
	divide_by_redirections(&words);
	process_dollar_values(words, shvars);
	proceess_tilde(words, shvars);

	IF_TERM(term_restore(&term_get_data()->old_term));
	IF_TERM(ft_putnewl());

	cmd_queue = group_words_by_delim(words, ";");
	process_cmds(cmd_queue, shvars, built_in_cmds);
	
	IF_TERM(term_enable_raw_mode(term_get_data()));

	del_groups_of_words(cmd_queue);
	del_lst_of_words(words);
}
