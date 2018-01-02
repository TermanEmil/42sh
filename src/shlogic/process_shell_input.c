#include "shlogic.h"

typedef t_lst_words	t_cmd_queue;
typedef t_lst_words	t_pipe_queue;

t_list	*divide_by_delim(t_lst_words *words, t_rostr delim)
{
	t_lst_words	*buf;
	t_list		*result;
	t_str		argv;

	buf = NULL;
	result = NULL;
	for (; words; LTONEXT(words))
	{
		argv = word_to_str(LCONT(words, t_lst_inkey*));
		if (argv == NULL)
			ft_err_mem(1);
		if (ft_strequ(argv, delim))
		{
			if (buf != NULL)
				ft_lstadd(&result, ft_lstnew_nocpy(buf, sizeof(buf)));
			buf = NULL;
		}
		else
			ft_lstadd(&buf, ft_lstnew_nocpy(
				LCONT(words, t_lst_inkey*), sizeof(t_lst_inkey*)));
		free(argv);
	}
	if (buf != NULL)
		ft_lstadd(&result, ft_lstnew_nocpy(buf, sizeof(buf)));
	return result;
}

void	del_groups_of_words(t_list *groups_of_words)
{
	t_list		*group;
	t_lst_words	*words;

	for (group = groups_of_words; group; LTONEXT(group))
	{
		words = LCONT(group, t_lst_words*);
		ft_lstdel(&words, NULL);
	}
	ft_lstdel(&groups_of_words, NULL);
}

void	debug_print_groups_of_words(const t_list *groups_of_words)
{
	t_str		*argv;
	int			i;

	for (i = 0; groups_of_words; LTONEXT(groups_of_words), i += 3)
	{
		argv = words_to_argv(LCONT(groups_of_words, t_lst_words*));
		debug_print_strings(argv, i);
		ft_free_bidimens(argv);
	}
}

void	process_pipe_queue(t_pipe_queue *pipe_queue)
{

}

void	process_cmds(t_cmd_queue *cmd_queue)
{
	t_pipe_queue	*pipe_queue;

	for (; cmd_queue; LTONEXT(cmd_queue))
	{
		pipe_queue = divide_by_delim(LCONT(cmd_queue, t_lst_words*), "|");
		process_pipe_queue(pipe_queue);
		del_groups_of_words(pipe_queue);
	}
}

void	process_shell_input(t_lst_inkey *keys, const t_shvars *shvars)
{
	t_lst_words	*words;
	t_str		*argv;

	words = extract_words_from_keys(keys);
	
	divide_by_redirections(&words);
	process_dollar_values(words, shvars);
	proceess_tilde(words, shvars);

	t_cmd_queue	*cmd_queue;

	cmd_queue = divide_by_delim(words, ";");
	process_cmds(cmd_queue);
	del_groups_of_words(cmd_queue);

	argv = words_to_argv(words);
	debug_print_strings(argv, 2);
	ft_free_bidimens(argv);
	del_lst_of_words(words);
}
