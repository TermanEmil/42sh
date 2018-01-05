#include "shlogic.h"
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>

static void		print_cd_errors_(t_rostr dir)
{
	ft_error(FALSE, "%s: cd: %s: %s\n", g_proj_name, dir, strerror(errno));
	errno = 0;
}

static int		set_env_vars_after_cd_(
					t_shvars *shvars,
					t_str old_pwd,
					t_str new_pwd)
{
	int		ret;

	ret = htab_set_pair(shvars->env, new_hashpair(
		new_hashmem_str("OLDPWD"), new_hashmem_str(old_pwd)));
	ret += htab_set_pair(shvars->env, new_hashpair(
		new_hashmem_str("PWD"), new_hashmem_str(new_pwd)));
	free(old_pwd);
	free(new_pwd);

	if (ret != 0)
		ft_err_mem(FALSE);
	
	return ret;
}

static int		cd_to_dir_(t_rostr dir, t_shvars *shvars)
{
	t_str		old_pwd;
	t_str		new_pwd;
	int			ret;

	if ((old_pwd = getcwd(NULL, 0)) == NULL)
	{
		ft_err_erno(errno, ERR_DONT_EXIT_PROG);
		return -1;
	}
	if (chdir(dir) != 0)
	{
		free(old_pwd);
		print_cd_errors_(dir);
		return -1;
	}
	if ((new_pwd = getcwd(NULL, 0)) == NULL)
	{
		free(old_pwd);
		ft_err_erno(errno, ERR_DONT_EXIT_PROG);
		return -1;
	}
	return set_env_vars_after_cd_(shvars, old_pwd, new_pwd);
}

static t_str	get_home_dir_(t_shvars *shvars)
{
	struct passwd	*buf;
	t_str			val;

	if ((val = htab_get_strval(shvars->env, new_hashmem_str("HOME"))) != NULL)
		return ft_strdup(val);
	if ((buf = getpwuid(getuid())) == NULL)
	{
		ft_proj_err("Can't find HOME dir", FALSE);
		return NULL;
	}
	return ft_strdup(buf->pw_name);
}

int				execute_cmd_cd(const t_str *argv, t_shvars *shvars)
{
	t_rostr	dir;

	if (argv[1] == NULL)
	{
		if ((dir = get_home_dir_(shvars)) != NULL)
			return cd_to_dir_(dir, shvars);
		else
			return -1;
	}
	else if (ft_strequ(argv[1], "-"))
	{
		dir = htab_get_strval(shvars->env, new_hashmem_str("OLDPWD"));
		if (dir == NULL)
		{
			ft_error(FALSE, "%s: cd: OLDPWD not set", g_proj_name);
			return -1;
		}
		return cd_to_dir_(dir, shvars);
	}
	else
		return cd_to_dir_(argv[1], shvars);
}
