#include "shell42.h"

static inline void	init_global_links(void)
{
	ft_err_init_proj_name("42sh");

	g_current_in = &g_shdata.input.current;
	g_shinput = &g_shdata.input;
}

void	init_shell(void)
{
	g_shdata = shdata_construct();

	init_global_links();

	term_setup(getenv("TERM"), term_get_data());
	term_make_termcap_keys_work();
	g_shdata.input.term_tty = term_get_current_tty();

	init_sh_events();
	shell_init_key_cmds_htab();
	
	listen_to_signals();
	ft_strcpy(g_shdata.prompt, DEFAULT_PROMPT);
}
