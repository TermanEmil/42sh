#include "shlogic.h"
#include "regex_tools.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


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
		execute_built_in(fd_io, exec_cmd_f, argv, shvars);
		// exec_cmd_f(argv, shvars);	
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

static void		process_pipe_redirs_(
					t_input_output *fd_io,
					const t_grps_wrds *pipe_queue,
					int fd_in,
					const int *pipe_fd)
{
	fd_io->in = fd_in;
	if (L_IS_LAST(pipe_queue))
		fd_io->out = STDOUT_FILENO;
	else
		fd_io->out = pipe_fd[g_write_end_];

	if (pipe_should_redir_stderr_(pipe_queue))
		fd_io->err = STDOUT_FILENO;
	else
		fd_io->err = STDERR_FILENO;
}

#define REG_TO_FILE_REDIR_	"[0-9]*[><]+"
#define REG_TO_FD_REDIR_	"[0-9]*[><]+&[0-9]+"
#define REG_CLOSE_FD_		"[0-9]*[><]+&-"

#define REG_ALL_3_REDIRS_	"("						\
							REG_TO_FILE_REDIR_ "|"	\
							REG_TO_FD_REDIR_ "|"	\
							REG_CLOSE_FD_")"		\

#define REG_ANY_FILE_REDIR_	"("						\
							REG_TO_FILE_REDIR_ "|"	\
							REG_TO_FD_REDIR_")"		\

static void		extract_fds_from_redir_(t_rostr redir_str, int *fd1, int *fd2)
{
	t_str	buf;
	t_rostr	start_of_redir;

	start_of_redir = ft_strnchr(redir_str, "><");
	if (start_of_redir == redir_str)
		*fd1 = -1;
	else
		*fd1 = ft_atoi(redir_str);

	buf = regex_get_match("[0-9]+", start_of_redir);

	if (buf == NULL)
		*fd2 = -1;
	else
	{
		*fd2 = ft_atoi(buf);
		free(buf);
	}
}

static int		process_redir_to_file_(
					t_input_output *fd_io,
					t_rostr redir_str,
					t_lst_words *next_words,
					t_list **fds_to_close)
{
	int		fd1;
	int		fd2;
	t_str	redir_type;
	t_str	after_redir_type;

	t_str	next_word_str;

	extract_fds_from_redir_(redir_str, &fd1, &fd2);
	redir_type = regex_get_match("[><]+", redir_str);
	after_redir_type =
		regex_get_match("(&|-)", redir_str + ft_strlen(redir_type));

	next_word_str = NULL;
	if (regex_mini_match(REG_ANY_FILE_REDIR_, redir_str))
	{
		if (next_words == NULL)
		{
			return -1;
		}

		next_word_str = word_to_argv(LCONT(next_words, t_lst_inkey*));
		if (next_word_str == NULL)
			ft_err_mem(TRUE);

		if (ft_strequ(redir_type, ">") || ft_strequ(redir_type, ">>") || ft_strequ(redir_type, "<"))
		{
			t_to_dup	to_dup;
			int			file_fd;
			int			open_flags;

			
			if (ft_strchr(redir_type, '>'))
			{
				open_flags = O_WRONLY | O_CREAT;
				if (ft_strequ(redir_type, ">>"))
					open_flags |= O_APPEND;
				else
					open_flags |= O_TRUNC;
			}
			else
				open_flags = O_RDONLY;

			file_fd = open(next_word_str, open_flags, 0644);
			if (file_fd == -1)
			{
				ft_error(FALSE, "%s: %s: %s\n",
					g_proj_name, next_word_str, strerror(errno));
				errno = 0;
				return -1;
			}
			else
			{
				if (fd1 >= 0)
				{
					to_dup.fd = file_fd;
					to_dup.default_fd = fd1;
					ft_lstadd(&fd_io->other, ft_lstnew(&to_dup, sizeof(to_dup)));
				}
				else
				{
					if (ft_strequ(redir_type, "<"))
						fd_io->in = file_fd;
					else
						fd_io->out = file_fd;
				}
				ft_lstadd(fds_to_close, ft_lstnew(&file_fd, sizeof(file_fd)));
			}
		}
		else
		{
			ft_error(FALSE,
				"%s: %s: invalid redirection\n", g_proj_name, redir_type);
		}

		ft_memdel((void**)&next_word_str);
	}
	else if (regex_mini_match(REG_CLOSE_FD_, redir_str))
	{

	}
	else
	{
		return -1;
	}
	// else if (regex_mini_match(REG_TO_FD_REDIR_, word_str))
	// {

	// }
	// else if (regex_mini_match(REG_CLOSE_FD_, word_str))
	// {

	// }

	ft_memdel((void**)&redir_type);
	ft_memdel((void**)&after_redir_type);
	return 0;
}

static void		process_file_redirs_(
					t_input_output *fd_io,
					const t_lst_words *words,
					int fd_in,
					const int *pipe_fd,
					t_list **fds_to_close)
{
	t_lst_inkey	*word_keys;
	t_str		word_str;

	for (; words; LTONEXT(words))
	{
		word_keys = LCONT(words, t_lst_inkey*);
		word_str = word_to_str(word_keys);
		if (word_str == NULL)
			ft_err_mem(TRUE);

		if (regex_mini_match(REG_ALL_3_REDIRS_, word_str))
			process_redir_to_file_(fd_io, word_str, words->next, fds_to_close);
		
		free(word_str);
	}
}

void			process_redirections(
					t_input_output *fd_io,
					const t_grps_wrds *pipe_queue,
					int *fd_in,
					int *pipe_fd,
					t_list **fds_to_close)
{
	fd_io->other = NULL;
	if (pipe(pipe_fd) == -1)
		ft_err_erno(errno, TRUE);

	process_pipe_redirs_(fd_io, pipe_queue, *fd_in, pipe_fd);
	process_file_redirs_(fd_io, LCONT(pipe_queue, t_lst_words*),
		*fd_in, pipe_fd, fds_to_close);

	*fd_in = pipe_fd[g_read_end_];
}

static void		close_lst_of_fds_(t_list *fds_to_close)
{
	for (; fds_to_close; LTONEXT(fds_to_close))
		close(*LCONT(fds_to_close, int*));
	errno = 0;
}

#define PIPE_DELIM_ "(\\||\\|&)"

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
	t_list			*fds_to_close;

	cmd_count = ft_lstlen(pipe_queue);
	fd = malloc(sizeof(int) * cmd_count * 2);

	for (i = 0; i < cmd_count * 2; i++)
		fd[i] = -1;

	fds_to_close = NULL;
	in = 0;
	for (i = 0; pipe_queue; LTONEXT(pipe_queue), i++)
	{
		words = LCONT(pipe_queue, t_lst_words*);
		if (words_match_single(words, PIPE_DELIM_))
			continue;

		argv = extract_argv(words);

		// for (int j = 0; argv[j]; j++)
		// 	ft_printf(":%s:\n", argv[j]);

		process_redirections(&fd_io, pipe_queue, &in, fd + i * 2, &fds_to_close);
		process_argv(fd_io, argv, shvars, built_in_cmds);

		if (close(fd[i * 2 + g_write_end_]) != 0)
			ft_err_erno(errno, TRUE);

		ft_free_bidimens(argv);
		ft_lstdel(&fd_io.other, &std_mem_del);
	}

	// It's ok if it didn't wait for anything.
	while (wait(NULL) > 0);

	if (errno == ECHILD)
		errno = 0;
	else
		ft_err_erno(errno, TRUE);

	close_lst_of_fds_(fds_to_close);
	ft_lstdel(&fds_to_close, &std_mem_del);

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

		pipe_queue = group_words_by_delim(words, PIPE_DELIM_);
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
