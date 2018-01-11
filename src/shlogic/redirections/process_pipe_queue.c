#include "shell_redirs_.h"
#include "shell42.h"

/*
** Extract all args from the given list of words until it finds a redirection.
*/

static t_str	*extract_argv_(const t_lst_words *words)
{
	t_str	*argv;
	t_str	tmp;
	int		i;

	argv = (t_str*)malloc((ft_lstlen(words) + 1) * sizeof(t_str));
	if (argv == NULL)
		ft_err_mem(TRUE);
	for (i = 0; words; LTONEXT(words), i++)
	{
		if (word_is_valid_redirection(LCONT(words, t_lst_inkey*)))
			break;
		else
		{
			tmp = word_to_argv(LCONT(words, t_lst_inkey*));
			if (tmp == NULL)
				ft_err_mem(TRUE);
			argv[i] = tmp;
		}
	}
	argv[i] = NULL;
	return argv;
}

/*
** Process all redirections of a pipe cmd, that is: pipe-ing, redirection to
** file or closing a fd. Here the cmd_env-s are created.
*/

static void		process_all_redirs_(
					t_pipe_env *pipe_env,
					const t_grps_wrds *queue_iter,
					int *pipe_fd,
					t_list **cmd_envs)
{
	t_cmd_env	cmd_env;
	t_str		*argv;

	if (words_match_single(LCONT(queue_iter, t_lst_words*), "^" PIPE_DELIM "$"))
		return;

	argv = extract_argv_(LCONT(queue_iter, t_lst_words*));
	cmd_env = new_cmd_env(argv, queue_iter, pipe_env->shvars, pipe_fd);

	process_redirections(pipe_env, &cmd_env);
	ft_lstadd(cmd_envs, ft_lstnew(&cmd_env, sizeof(cmd_env)));
}

/*
** Execute the arguments, closing the writing end of the pipe (important).
*/

static int		execute_argvs_of_cmd_envs_(
					t_pipe_env *pipe_env,
					t_list *cmd_envs)
{
	t_cmd_env	*cmd_env;
	int			ret;

	for (; cmd_envs; LTONEXT(cmd_envs))
	{
		cmd_env = LCONT(cmd_envs, t_cmd_env*);
		if (cmd_env->success)
			ret = process_argv(pipe_env, cmd_env);

		if (cmd_env->piped_fds[PIPE_WRITE_END] >= 0)
		{
			if (TMP_FAIL_RETRY(close(cmd_env->piped_fds[PIPE_WRITE_END])) != 0)
				ft_err_erno(errno, TRUE);
			cmd_env->piped_fds[PIPE_WRITE_END] = -1;
		}
		if (ret == -2)
			return ret;
	}
	return 0;
}

/*
** pipe_env, cmd_env and redir_env are used to move data across functions and
** to keep the code intuitive.
**
** First, an array of integers for pipe-ing is created, so that the unecessary
** fd-s can be closed later.
**
** Then, a list of cmd_envs is created. Each pipe cmd (cmd1 | cmd2 ||| cmd3...)
** is processed, meaning that the necessary t_input_output structure (fd_io)
** inside cmd_env will be set, meaning that firstly, the necessary piping and
** file creation (for redirection) is created.
**
** Finally, each cmd_env is executed.
**
** To keept stuff simplier, pipe_env shares a list of integers: fds_to_close.
** This list stores all extra fd-s that appear during processing, for example
** when the output is redirected to a file, that fd is stored here.
**
** process_pipe_queue -> process_all_redirs_ -> process_redirections ->
** {
**  process_pipe_redirs -> ...
**  process_all_guillemet_redirs -> process_guillemet_redir -> ...
** }
*/

int			process_pipe_queue(t_pipe_env pipe_env)
{
	const t_grps_wrds	*queue_iter;
	int					*fd;
	int					i;
	t_list				*cmd_envs;
	int					ret;

	fd = new_fd_tab_for_piping(pipe_env.cmd_count * 2);

	queue_iter = pipe_env.pipe_queue;
	for (i = 0, cmd_envs = NULL; queue_iter; LTONEXT(queue_iter), i++)
		process_all_redirs_(&pipe_env, queue_iter, fd + i * 2, &cmd_envs);
	ret = execute_argvs_of_cmd_envs_(&pipe_env, cmd_envs);

	ft_lstdel(&cmd_envs, (t_ldel_func*)&del_cmd_env);

	wait_for_all_children_to_die_muhaha();
	g_shdata.running_a_process = FALSE;
	close_all_fds(pipe_env.fds_to_close, fd, pipe_env.cmd_count);
	
	ft_lstdel(&pipe_env.fds_to_close, &std_mem_del);
	ft_memdel((void**)&fd);
	return ret;
}
