#include "shell42.h"
#include <fcntl.h>
#include "ft_key_codes.h"
#include <time.h>
#include "shellvars.h"
#include <regex.h>
#include <stdio.h>

t_shdata		g_shdata;
t_shinput		*g_shinput;
t_current_input	*g_current_in;

// \\([0-9]*[><]\\+\\|[0-9]*[><]*\\&[0-9]*\\|[0-9]*[><]*\\&-\\)

#define FIRST_PART "\\(^\\|[ \t\n]\\+\\)"

int		main(int argc, const char **argv, const char **envp)
{
	// t_lst_str	*matches;
	// t_lst_str	*match;

	// matches = ft_regex_matchall(
	// 	"\\("
	// 	FIRST_PART "[0-9]*[><]\\+\\|"
	// 	FIRST_PART "[0-9]*[><]*\\&[0-9]*" "\\($\\|[ \t\n]\\+\\)" "\\|"
	// 	FIRST_PART "[0-9]*[><]*\\&-\\|"
	// 	";\\|"
	// 	"|\\)",
	// 	"\"a > b\";cd"
	// 	// " >>"
	// 	// " ><"
	// 	// " <"
	// 	// " <<"
	// 	// " <<>>><<>"
	// 	// " 99>"
	// 	// " 99>&-"
	// 	// " 99>&99"
	// 	// " 99>filename"
	// 	, 0, 0, TRUE);

	// int i = 0;
	// for (match = matches; match; LTONEXT(match), i++)
	// {
	// 	ft_printf("%d) %s\n", i, LSTR(match));
	// }

	// ft_lstdel(&matches, &std_mem_del);

	init_shell(envp);

	ft_putstr("42sh shell by eterman");
	term_putnewl();
	input_reprint_here(g_current_in);

	while (1)
	{
		shinput_reset_signals(g_shinput);
		shell_read_user_input();
		shinput_process_signals(g_shinput);
	}
	event_exit(0);
}