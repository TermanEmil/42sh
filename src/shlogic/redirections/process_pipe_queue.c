#include "shell_redirs_.h"
#include "shlogic.h"
#include "regex_tools.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

pid_t	process_argv(
			t_pipe_env *pipe_env,
			t_cmd_env *cmd_env)
{
	t_str			cmd_path;
	t_exec_cmd_f	*exec_cmd_f;
	pid_t			ret;

	if (cmd_env->argv[0] != NULL && cmd_is_set_var(cmd_env->argv[0]))
	{
		execute_cmd_set_local_var(cmd_env);
		return 0;
	}
	else if ((exec_cmd_f = get_sh_builtin_f(cmd_env->argv[0], pipe_env->built_in_cmds)))
	{
		execute_built_in(cmd_env, exec_cmd_f);
		return 0;
	}
	else if (cmd_is_specific_program(cmd_env->argv[0]))
		return execute_cmd(cmd_env, cmd_env->argv[0]);
	else if ((cmd_path = find_cmd_in_env_path(cmd_env->argv[0], pipe_env->shvars)))
	{
		ret = execute_cmd(cmd_env, cmd_path);
		free(cmd_path);
		return ret;
	}

	ft_error(FALSE, "%s: command not found\n", cmd_env->argv[0]);
	return -1;
}

t_bool	word_is_valid_redirection(const t_lst_inkey* in_keys)
{
	t_str	tmp;
	t_bool	condition;

	tmp = word_to_str(in_keys);
	if (tmp == NULL)
		ft_err_mem(TRUE);
	condition = ft_strnchr(tmp, "><") && !ft_strnchr(tmp, "\"\'\\`()[]{}");	
	free(tmp);
	return condition;
}

/*
** Extract all args from the given list of words until it finds a redirection.
*/

t_str	*extract_argv(const t_lst_words *words)
{
	t_str	*argv;
	t_str	tmp;
	int		i;
	t_bool	condition;

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

static void	process_pipe_queue_iter_(
				t_pipe_env *pipe_env,
				const t_grps_wrds *queue_iter,
				int *pipe_fd)
{
	t_cmd_env			cmd_env;
	t_str				*argv;

	if (words_match_single(LCONT(queue_iter, t_lst_words*), PIPE_DELIM))
		return;

	argv = extract_argv(LCONT(queue_iter, t_lst_words*));
	cmd_env = new_cmd_env(argv, queue_iter, pipe_env->shvars, pipe_fd);

	process_redirections(pipe_env, &cmd_env);
	if (pipe_env->success)
		process_argv(pipe_env, &cmd_env);

	if (close(cmd_env.piped_fds[PIPE_WRITE_END]) != 0)
		ft_err_erno(errno, TRUE);

	ft_free_bidimens(argv);
	ft_lstdel(&cmd_env.fd_io.other, &std_mem_del);
}

void	process_pipe_queue(t_pipe_env pipe_env)
{
	const t_grps_wrds	*queue_iter;
	int					*fd;
	int					i;

	fd = new_fd_tab_for_piping(pipe_env.cmd_count * 2);

	queue_iter = pipe_env.pipe_queue;
	for (i = 0; queue_iter; LTONEXT(queue_iter), i++)
		process_pipe_queue_iter_(&pipe_env, queue_iter, fd + i * 2);

	wait_for_all_children_to_die_muhaha();
	close_all_fds(pipe_env.fds_to_close, fd, pipe_env.cmd_count);
	
	ft_lstdel(&pipe_env.fds_to_close, &std_mem_del);
	ft_memdel((void**)&fd);
}
