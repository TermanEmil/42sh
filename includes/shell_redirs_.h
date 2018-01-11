#ifndef _SHELL_REDIRS__H_
# define _SHELL_REDIRS__H_

# include "shlogic.h"

# define PIPE_READ_END	0
# define PIPE_WRITE_END	1
# define PIPE_DELIM "(\\||\\|&)"

# define REG_TO_FILE_REDIR	"[0-9]*[><]+"
# define REG_TO_FD_REDIR	"[0-9]*[><]+&[0-9]+"
# define REG_CLOSE_FD		"[0-9]*[><]+&-"

typedef struct		s_redir_env
{
	t_rostr			redir;
	t_str			redir_type;
	int				left_fd;
	int				right_fd;
	t_str			next_word_str;
}					t_redir_env;

/*
** Public.
*/

int		process_pipe_queue(t_pipe_env pipe_env);
pid_t	process_argv(t_pipe_env *pipe_env, t_cmd_env *cmd_env);

/*
** The actual redirs.
*/

void	process_redirections(t_pipe_env *pipe_env, t_cmd_env *cmd_env);
void	process_pipe_redirs(t_cmd_env *cmd_env, int current_pipe_input_fd);

void	process_all_guillemet_redirs(t_pipe_env *pipe_env, t_cmd_env *cmd_env);
void	extract_fds_from_redir(t_rostr redir_str, int *fd1, int *fd2);
void	process_guillemet_redir(t_pipe_env *pipe_env, t_cmd_env *cmd_env,
			t_rostr redir_str, t_lst_words *next_words);
void	process_guillemet_close_fd(t_cmd_env *cmd_env, t_redir_env *redir_env);
void	process_guillemet_redir_to_from_file(t_pipe_env *pipe_env,
			t_cmd_env *cmd_env, t_redir_env *redir_env);

/*
** Utils
*/

int		*new_fd_tab_for_piping(int size);
void	wait_for_all_children_to_die_muhaha();
void	close_all_fds(
			const t_lst_int *fds_to_close, const int *fd, int cmd_count);
t_bool	word_is_valid_redirection(const t_lst_inkey* in_keys);

/*
** Constructors & destructors
*/

t_pipe_env	new_pipe_env(const t_grps_wrds *pipe_queue,
				const t_hashtab *built_in_cmds, t_shvars *shvars);
t_cmd_env	new_cmd_env(t_str *argv, const t_grps_wrds *pipe_queue_iter,
				t_shvars *shvars, int *piped_fds);
void		del_cmd_env(t_cmd_env *cmd_env);
t_to_dup	new_to_dup(int fd, int default_fd, t_bool to_close);
t_redir_env	new_redir_env(t_rostr redir, t_lst_words *next_words);
void		del_redir_env(t_redir_env *redir_env);

#endif