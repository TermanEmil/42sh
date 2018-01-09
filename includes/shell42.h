#ifndef SHELL42_H
# define SHELL42_H

# include <stdio.h>
# include "libft.h"
# include "listlib.h"
# include "ft_errors.h"
# include "ft_colors.h"
# include "short_named_types.h"
# include "shinput.h"
# include "termlib.h"
# include "eventlib.h"
# include "hashtablib.h"
# include "shlogic.h"
# include "shellvars.h"

# define DEFAULT_PROMPT "[42sh]$>"

# define IF_TERM(cmd)				\
	if (g_shdata.is_term)			\
		cmd;						\

# define IF_TERM2(cmd1, cmd2)		\
	if (g_shdata.is_term)			\
		cmd1;						\
	else							\
		cmd2;						\


typedef struct s_shdata			t_shdata;

extern t_shdata		g_shdata;

struct				s_shdata
{
	char			prompt[36];
	t_shinput		input;
	t_shvars		shvars;
	t_hashtab		*built_in_cmds;
	t_bool			running_a_process;
	t_bool			is_term;
};

void				read_process_non_term_input();

/*
** shdata: get, set
*/

char const			*shell_get_prompt(void);

/*
** Signals
*/

void				listen_to_signals(void);

/*
** Initializers
*/

void				init_shell(const char **envp);
void				init_sh_events(void);

/*
** Constructors
*/

t_shdata			shdata_construct(void);

/*
** Destructors
*/

void				shdata_destruct(t_shdata *target);

/*
** Utils
*/

t_lst_str			*ft_regex_matchall(t_rostr patern, t_rostr str,
						int patern_flags, int str_flags, t_bool verbose);


#endif
