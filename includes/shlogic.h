#ifndef SHLOGIC_H
# define SHLOGIC_H

# include "shellvars.h"
# include "listlib.h"
# include "shinput.h"

# define CHILD_PROCESS_PID 0

/*
** A list of list of t_sh_inkeys.
** First key from the first word:
** LCONT((LCONT(words, t_list*)), t_sh_inkey*)
*/

typedef t_list					t_lst_words;

/*
** t_grps_wrds stands for: list of groups of words.
*/

typedef t_lst_words				t_grps_wrds;
typedef t_list					t_lst_to_dup;
typedef struct s_cmd_env		t_cmd_env;
typedef int						(t_exec_cmd_f)(t_cmd_env*);

typedef struct			s_to_dup
{
	int					fd;
	int					default_fd;
	t_bool				to_close;
}						t_to_dup;

typedef struct			s_input_output
{
	int					in;
	int					out;
	int					err;
	t_lst_to_dup		*other;
}						t_input_output;

struct					s_cmd_env
{
	t_shvars			*shvars;
	t_input_output		fd_io;
	t_str				*argv;
	int					*piped_fds;
	const t_grps_wrds	*pipe_queue_iter;
	t_bool				success;
};

typedef struct			s_pipe_env
{
	const t_grps_wrds	*pipe_queue;
	const t_hashtab		*built_in_cmds;
	t_shvars			*shvars;
	t_lst_int			*fds_to_close;
	int					cmd_count;
	int					current_pipe_input_fd;
}						t_pipe_env;

/*
** execute_cmd
*/

void		execute_cmd_exit();
int			execute_cmd_cd(t_cmd_env *cmd_env);
int			execute_cmd_env(t_cmd_env *cmd_env);
int			execute_cmd_setenv(t_cmd_env *cmd_env);
int			execute_cmd_unsetenv(t_cmd_env *cmd_env);
int			execute_cmd_set_local_var(t_cmd_env *cmd_env);

/*
** Initializers
*/

t_hashtab	*init_built_in_cmds_htab();

/*
** Destructors
*/

void		del_lst_of_words(t_lst_words *words);
void		del_lst_of_words_not_content(t_lst_words *words);

/*
** lst of words
*/

t_lst_words	*extract_words_from_keys(t_lst_inkey const *keys);
void		process_dollar_values(
						t_lst_words *words, const t_shvars *shvars);
void		divide_by_redirections(t_lst_words **words);

/*
** Groupds of words.
*/

t_grps_wrds	*group_words_by_delim(t_lst_words *words,
						t_rostr delim_reg_patern);
void		del_groups_of_words(t_grps_wrds *groups_of_words);
void		debug_print_groups_of_words(
						const t_grps_wrds *groups_of_words);

/*
** Main
*/

void		process_shell_input(t_lst_inkey *keys, t_shvars *shvars,
				const t_hashtab *built_in_cmds);

/*
** Word processing (both in same file).
*/

t_str		word_to_argv(const t_lst_inkey *keys);
t_str		*words_to_argv(t_lst_words *words);

/*
** Tilde
*/

void		proceess_tilde(t_lst_words	*words, const t_shvars *shvars);
t_lst_inkey	*process_tilde_in_word(const t_lst_inkey *word,
				const t_shvars *shvars);
t_str		get_tilde_prefix(const t_lst_inkey *keys, int *len);
t_str		get_tilde_value(t_rostr tilde_prefix, const t_shvars *shvars);

/*
** execute_cmd: utils
*/

t_bool		cmd_is_set_var(t_rostr str);
t_bool		cmd_is_specific_program(t_rostr cmd);
t_str		find_cmd_in_env_path(t_rostr cmd, const t_shvars *shvars,
				t_bool is_regex_patern);
t_exec_cmd_f *get_sh_builtin_f(t_rostr cmd, const t_hashtab *built_in);
pid_t		execute_cmd(t_cmd_env *cmd_env, t_rostr cmd_path);
void		execute_built_in(t_cmd_env *cmd_env, t_exec_cmd_f *cmd_f);
void		dup_and_close(int fd, int default_fd, t_bool close_it);
void		dup_and_closelst(const t_lst_to_dup *lst_to_dup, t_bool close_it);

/*
** Utils
*/

void		debug_print_strings(t_str *strings, int top_start);
t_str		extract_var_name_from_keys(const t_lst_inkey *keys);
t_str		word_to_str(const t_lst_inkey *keys);
t_bool		word_matches(const t_lst_inkey *word_keys, t_rostr patern);
t_bool		words_match_single(const t_lst_words *words,
				t_rostr patern);

#endif
