#include "shlogic.h"
#include "shell42_utils.h"
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
			const t_str *argv,
			t_shvars *shvars,
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
	else if ((exec_cmd_f = get_sh_builtin_f(argv[0], built_in_cmds)))
	{
		exec_cmd_f(argv, shvars);
		return 0;
	}
	else if (cmd_is_specific_program(argv[0]))
		return execute_cmd(fd_io, argv[0], argv, shvars);
	else if ((cmd_path = find_cmd_in_env_path(argv[0], shvars)))
	{
		ret = execute_cmd(fd_io, cmd_path, argv, shvars);
		free(cmd_path);
		return ret;
	}

	ft_error(FALSE, "%s: command not found\n", argv[0]);
	return -1;
}

static const int	g_read_end_ = 0;
static const int	g_write_end_ = 1;

static const t_rostr	g_regex_redir_patern_ = 
	"("
	"[0-9]*[><]+" "|"
	"[0-9]*[><]+&[0-9]+" "|"
	"[0-9]*[><]+&-"
	")";

/*
** If the next pipe is a |&, then stderr should redirectionate to stdout.
*/

static t_bool	pipe_should_redir_stderr_(const t_grps_wrds *next_group)
{
	const t_lst_words	*words;

	if (next_group->next == NULL)
		return FALSE;

	words = LCONT(next_group->next, t_lst_words*);
	return words_match_single(words, "\\|&");
}

t_input_output	process_redirections(
					t_grps_wrds *pipe_queue,
					int *fd_in,
					int *pipe_fd)
{
	t_input_output	fd_io;

	if (pipe(pipe_fd) == -1)
		ft_err_erno(errno, TRUE);

	fd_io.in = *fd_in;
	if (pipe_queue->next == NULL)
		fd_io.out = STDOUT_FILENO;
	else
		fd_io.out = pipe_fd[g_write_end_];

	if (pipe_should_redir_stderr_(pipe_queue))
		fd_io.err = STDOUT_FILENO;
	else
		fd_io.err = STDERR_FILENO;

	*fd_in = pipe_fd[g_read_end_];
	return fd_io;
}

void	process_pipe_queue(
			t_grps_wrds *pipe_queue,
			t_shvars *shvars,
			const t_hashtab *built_in_cmds)
{
	t_str			*argv;
	t_lst_words		*words;
	int				*fd;
	t_input_output	fd_io;
	int				in;
	int				i;
	int				cmd_count;

	cmd_count = ft_lstlen(pipe_queue);
	fd = malloc(sizeof(int) * cmd_count * 2);

	for (i = 0; i < cmd_count * 2; i++)
		fd[i] = -1;

	in = 0;
	for (i = 0; pipe_queue; LTONEXT(pipe_queue), i++)
	{
		words = LCONT(pipe_queue, t_lst_words*);
		if (words_match_single(words, PIPE_DELIM))
			continue;

		argv = extract_argv(words);

		// for (int j = 0; argv[j]; j++)
		// 	ft_printf(":%s:\n", argv[j]);

		fd_io = process_redirections(pipe_queue, &in, fd + i * 2);
		process_argv(fd_io, argv, shvars, built_in_cmds);

		if (close(fd[i * 2 + g_write_end_]) != 0)
			ft_err_erno(errno, TRUE);

		ft_free_bidimens(argv);
	}

	// It's ok if it didn't wait for anything.
	while (wait(NULL) > 0);

	if (errno == ECHILD)
		errno = 0;
	else
		ft_err_erno(errno, TRUE);

	for (i = 0; i < cmd_count; i++)
		if (fd[i * 2 + g_read_end_] != -1 && close(fd[i * 2 + g_read_end_]) != 0)
			errno = 0;

	free(fd);
}

void	process_cmds(
			t_grps_wrds *cmd_queue,
			t_shvars *shvars,
			const t_hashtab *built_in_cmds)
{
	t_grps_wrds	*pipe_queue;
	t_lst_words	*words;

	for (; cmd_queue; LTONEXT(cmd_queue))
	{
		words = LCONT(cmd_queue, t_lst_words*);
		if (words_match_single(words, ";"))
			continue;

		pipe_queue = group_words_by_delim(words, PIPE_DELIM);
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

	t_grps_wrds	*cmd_queue;

	cmd_queue = group_words_by_delim(words, ";");

	term_restore(&term_get_data()->old_term);
	ft_putnewl();
	process_cmds(cmd_queue, shvars, built_in_cmds);
	term_enable_raw_mode(term_get_data());

	del_groups_of_words(cmd_queue);
	del_lst_of_words(words);
}
