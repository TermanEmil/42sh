#ifndef SHINPUT_H
# define SHINPUT_H

# include "listlib.h"
# include "ft_errors.h"
# include "hashtablib.h"

# define SHELL_INPUT_DELIMS " _;\"'-{[()]}|`#"

/*
** There are some cases when you can input an escape character (\033). When
** you do that, the terminal outputs '^[' (2 characters). When you backspace
** it, the terminal removes the both characters. But the terminal still
** remembers that it's '\033'. For that I created s_sh_inkey.
**
** Configured from scripts: s_input_history.nb_of_inputs_to_remember
*/

/*
** Structure forward declarations
*/

typedef struct s_sh_inkey		t_sh_inkey;
typedef struct s_shinput_seq	t_shinput_seq;
typedef struct s_input_history	t_input_history;
typedef struct s_current_input	t_current_input;
typedef struct s_shinput		t_shinput;

/*
** List aliasses
*/

typedef t_list					t_lst_inkey;
typedef t_list					t_lst_input_seq;

/*
** t_key_cmd_f return [0, inf)
*/

typedef int						(t_key_cmd_f)(void);

extern t_shinput				*g_shinput;
extern t_current_input			*g_current_in;

/*
** This structure defines one key. If the user inserts 'a', then this strucutre
** would have the following values: {displayed_chars = "a", meaning = NULL}.
** If the insertion is '\033' then {displayed_chars = "^[", meaning = "\033"}.
** So, if the meaning is NULL, then both displayed_chars and meaning are the
** same.
**
** is_true_char - if the key is in quotes of backslashed, it won't suffer any
** further processing. Ex: '"' here, only the double quotes will be true char.
*/

struct				s_sh_inkey
{
	char			*displayed_chars;
	char			*meaning;
	t_bool			is_true_char;
	int				word_id;
};

/*
** An user command or input (until enter is pressed). Data to be saved in
** history.
*/

struct				s_shinput_seq
{
	t_lst_inkey		*keys;
	size_t			count;
};

/*
** nb_of_inputs_to_remember can be configured by the user from a configuration
** script.
** The default value should be eliminated when the script initialization
** is implemented.
** current_in_index is normally -1 and it stores only the current_in seq, when
** the user searches for another input in history.
*/

static size_t const	input_history_inputs_to_remember_default = 1024;

struct				s_input_history
{
	t_lst_input_seq	*inputs;
	size_t			count;
	size_t			nb_of_inputs_to_remember;
	t_shinput_seq	*tmp_current_in;
	int				current_in_index;
};

/*
** Defines the current user input. In case it's negative, the cursor isn't
** displayed.
** The cursor position is relative to the current input only.
** line_index is 0 by default
*/

struct				s_current_input
{
	t_shinput_seq	*input;
	ssize_t			cursor_pos;
	size_t			line_index;
};

/*
** Controlls the overall input.
*/

struct				s_shinput
{
	t_current_input	current;
	t_input_history	history;
	t_hashtab		*key_cmds;
	int				term_tty;
	t_bool			signaled_sigint;
};

/*
** Public
*/

void				shell_read_user_input(void);

/*
** Key cmds (in src/input/key_cmds)
*/

void				shell_init_key_cmds_htab(void);
t_hashpair const	*shell_get_key_cmd(char const *key_str);

/*
** ** Arrows
*/

int					key_cmd_arrow_left(void);
int					key_cmd_arrow_right(void);
int					key_cmd_arrow_down(void);
int					key_cmd_arrow_up(void);
int					key_cmd_ctrl_arrow_left(void);
int					key_cmd_ctrl_arrow_right(void);
int					key_cmd_alt_up(void);
int					key_cmd_alt_down(void);

/*
** ** Enter
*/

int					key_cmd_enter(void);
int					key_cmd_enter_process_parenthesis(void);

/*
** ** Other
*/

int					key_cmd_backspace(void);
int					key_cmd_home(void);
int					key_cmd_end(void);
int					key_cmd_home(void);
int					key_cmd_end(void);
int					key_cmd_ctrl_r(void);

/*
** Shell functions
*/

void				shell_get_cursor_pos(int *x, int *y);

/*
** Constructors
*/

t_sh_inkey			sh_inkey_construct(char *displayed_chars, char *meaning);
t_shinput_seq		shinput_seq_construct(void);
t_shinput_seq		*shinput_seq_new(void);
t_input_history		input_history_construct(void);
t_current_input		current_input_construct(void);
t_shinput			shinput_construct(void);

/*
** Destructors
*/

void				sh_inkey_destruct(t_sh_inkey *target);
void				shinput_seq_destruct(t_shinput_seq *target);
void				input_history_destruct(t_input_history *target);
void				current_input_destruct(t_current_input *target);
void				shinput_destruct(t_shinput *target);

/*
** t_sh_inkey
*/

char				*sh_inkey_get_meaning(t_sh_inkey const *target);
t_rostr				sh_inkey_get_pure_meaning(t_sh_inkey const *key);
size_t				sh_inkey_get_symbols(t_sh_inkey const *key);
t_sh_inkey			sh_inkey_get_from_raw(char const *raw);
char const			*get_displayed_alternative(char const *str, size_t *len);
t_bool				sh_inkey_is_delim(t_sh_inkey const *key);
void				uinput_print_seq(size_t seq_len);
t_sh_inkey			*sh_inkey_cpy(t_sh_inkey const *target);
t_str				lst_in_key_get_pure_str(
						t_lst_inkey const *lst, t_rostr delim);

/*
** t_shinput_seq
*/

void				input_seq_add_key(t_shinput_seq *target,
						t_sh_inkey key);
void				input_seq_insert_key(t_shinput_seq *seq,
						t_sh_inkey key, size_t index);
void				input_seq_insert_seq(t_shinput_seq *seq, size_t index,
						t_shinput_seq *to_insert);
void				input_seq_rm_key_at(t_shinput_seq *seq, size_t index);
size_t				input_count_symbols(t_lst_inkey const *head,
						ssize_t start, ssize_t end);
t_shinput_seq		*input_seq_cpy(t_shinput_seq const *seq);

/*
** ** Getters
*/

size_t				input_seq_get_disp_len(t_shinput_seq const *seq,
						size_t starting_with);
size_t				input_seq_get_meaning_len(t_shinput_seq const *seq,
						size_t starting_with);
char				*input_seq_get_displayed(t_shinput_seq const *seq,
						size_t starting_with);
char				*input_seq_get_meaning(t_shinput_seq const *seq,
						size_t starting_with);
char				*input_seq_get_displayed_range(t_shinput_seq const *seq,
						ssize_t start, ssize_t end);

/*
** t_input_history
*/

void				input_history_add_seq(t_input_history *target,
						t_shinput_seq shinput_seq);
void				history_set_current_in(t_input_history *history,
						t_current_input *current_in, int i);
void				history_change_seq_at(t_input_history *history,
						t_shinput_seq *new_seq, int i);

/*
** t_current_input
*/

int					input_reprint(t_current_input const *current_in);
int					input_reprint_here(t_current_input const *current_in);
int					current_input_mv_cursor_pos(ssize_t delta);
void				current_in_resset(t_current_input *current_in,
						t_bool destroy_seq);
char				*current_input_all_lines_to_str(
						t_current_input const *current_in, t_rostr delim);
char				current_input_is_complete(t_current_input const *input);
t_lst_inkey			*current_in_all_lines_to_lst(t_current_input *c_in,
						t_input_history *history);

/*
** t_shinput
*/

void				input_mv_cursor_at_start(t_current_input *current_in);
void				input_mv_current_in_to_history(t_shinput *input);

/*
** Signals
*/

void				shinput_reset_signals(t_shinput *shinput);
void				current_in_handle_sigint(t_shinput *shinput);
void				shinput_process_signals(t_shinput *shinput);

/*
** Other
*/

char const			*shell_read_user_input_key(void);

/*
** Utils
*/

char				ft_str_shell_parenthesis_are_complete(t_rostr str);

/*
** Debuggers
*/

void				ft_print_key(char const *str);
void				print_current_disp_at_top(void);
t_str				debug_get_history(t_input_history const *hist);

#endif