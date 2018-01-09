#include "shlogic.h"

int				execute_cmd_unsetenv(t_cmd_env *cmd_env)
{
	const t_str	*argv;

	argv = cmd_env->argv;
	if (argv[1] == NULL)
	{
		ft_error(FALSE, "%s: unsetenv: Invalid parameters\n", g_proj_name);
		return -1;
	}
	htab_remove(cmd_env->shvars->env, new_hashmem_str(argv[1]));
	if (errno)
	{
		ft_err_erno(errno, FALSE);
		errno = 0;
		return -1;
	}
	return 0;
}
