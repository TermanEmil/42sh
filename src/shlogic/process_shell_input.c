#include "shlogic.h"
#include <sys/wait.h>

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
			tmp = word_to_display_str(LCONT(words, t_lst_inkey*));
			if (tmp == NULL)
				ft_err_mem(TRUE);
			argv[i] = tmp;
		}
	}
	argv[i] = NULL;
	return argv;
}

pid_t	process_argv(
			t_input_output fd_io,
			const t_str *argv, t_shvars *shvars,
			const t_hashtab *built_in_cmds)
{
	t_str			cmd_path;
	t_exec_cmd_f	*exec_cmd_f;
	pid_t			ret;

	if (argv[0] != NULL && cmd_is_set_var(argv[0]))
	{
		execute_cmd_set_local_var(argv, shvars);
		return 0;
	}

	if ((exec_cmd_f = get_sh_builtin_f(argv[0], built_in_cmds)))
	{
		exec_cmd_f(argv, shvars);
		return 0;
	}

	if (cmd_is_specific_program(argv[0]))
		return execute_cmd(fd_io, argv[0], argv, shvars);

	if ((cmd_path = find_cmd_in_env_path(argv[0], shvars)))
	{
		ret = execute_cmd(fd_io, cmd_path, argv, shvars);
		free(cmd_path);
		return ret;
	}
	return -1;
}

static const int	g_read_end_ = 0;
static const int	g_write_end_ = 1;

void	process_pipe_queue(
			t_pipe_queue *pipe_queue,
			t_shvars *shvars,
			const t_hashtab *built_in_cmds)
{
	t_str			*argv;
	t_lst_words		*words;

	int				fd[2];
	t_input_output	fd_io;
	int				ret;
	int				in;

	in = 0;
	for (; pipe_queue; LTONEXT(pipe_queue))
	{
		words = LCONT(pipe_queue, t_lst_words*);
		argv = extract_argv(words);

		if (pipe_queue->next)
		{
			if (pipe(fd) == -1)
				ft_proj_err("Creating a pipe failed (1)", TRUE);

			fd_io.in = in;
			fd_io.out = fd[g_write_end_];

			process_argv(fd_io, argv, shvars, built_in_cmds);
			in = fd[g_read_end_];
			close(fd[g_write_end_]);
		}
		else
		{
			fd_io.in = in;
			fd_io.out = 1;
			process_argv(fd_io, argv, shvars, built_in_cmds);
		}
		ft_free_bidimens(argv);
	}

	// It's ok if it didn't wait for anything.
	while (wait(NULL) > 0);
	if (errno == ECHILD)
		errno = 0;
	else
		ft_err_erno(errno, TRUE);
}

void	process_cmds(
			t_cmd_queue *cmd_queue,
			t_shvars *shvars,
			const t_hashtab *built_in_cmds)
{
	t_pipe_queue	*pipe_queue;

	for (; cmd_queue; LTONEXT(cmd_queue))
	{
		pipe_queue = group_words_by_delim(LCONT(cmd_queue, t_lst_words*), "|");
		process_pipe_queue(pipe_queue, shvars, built_in_cmds);
		del_groups_of_words(pipe_queue);
	}
}

void	process_shell_input(
			t_lst_inkey *keys,
			t_shvars *shvars,
			const t_hashtab *built_in_cmds)
{
	t_lst_words	*words;
	t_str		*argv;

	words = extract_words_from_keys(keys);
	
	divide_by_redirections(&words);
	process_dollar_values(words, shvars);
	proceess_tilde(words, shvars);

	t_cmd_queue	*cmd_queue;

	cmd_queue = group_words_by_delim(words, ";");
	
	term_restore(&term_get_data()->old_term);
	ft_putnewl();
	process_cmds(cmd_queue, shvars, built_in_cmds);
	term_enable_raw_mode(term_get_data());

	del_groups_of_words(cmd_queue);
	del_lst_of_words(words);
}
