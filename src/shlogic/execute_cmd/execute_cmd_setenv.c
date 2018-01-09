#include "shlogic.h"

int				execute_cmd_setenv(t_cmd_env *cmd_env)
{
	const t_str	*argv;

	argv = cmd_env->argv;
	if (argv[1] == NULL)
	{
		ft_error(FALSE, "%s: setenv: Invalid parameters\n", g_proj_name);
		return -1;
	}
	htab_set_pair(cmd_env->shvars->env, new_hashpair(
		new_hashmem_str(argv[1]),
		new_hashmem_str((argv[2] == NULL) ? "" : argv[2])));
	if (errno)
	{
		ft_err_erno(errno, FALSE);
		errno = 0;
		return -1;
	}
	return 0;
}
