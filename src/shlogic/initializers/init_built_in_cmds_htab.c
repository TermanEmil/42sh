#include "shell42.h"

static void		add_cmd_(t_hashtab *htab, t_rostr cmd_name, const void *f)
{
	hashtab_add_pair(htab,
		new_hashpair_mllc(
			new_hashmem_str((t_str)cmd_name),
			new_hashmem((void*)f, sizeof(f))));
}

t_hashtab		*init_built_in_cmds_htab()
{
	t_hashtab	*htab;

	htab = new_hashtab(16, NULL, NULL);
	add_cmd_(htab, "exit", (t_exec_cmd_f*)&execute_cmd_exit);
	add_cmd_(htab, "cd", &execute_cmd_cd);
	add_cmd_(htab, "env", &execute_cmd_env);
	add_cmd_(htab, "setenv", &execute_cmd_setenv);
	add_cmd_(htab, "export", &execute_cmd_setenv);
	add_cmd_(htab, "unsetenv", &execute_cmd_unsetenv);
	add_cmd_(htab, "unset", &execute_cmd_unsetenv);
	return htab;
}
