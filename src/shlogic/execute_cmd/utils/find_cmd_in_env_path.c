#include "shlogic.h"
#include <sys/types.h>
#include <dirent.h>

static t_str	find_cmd_in_specific_path_(t_rostr path, t_rostr cmd)
{
	DIR				*dir_path;
	struct dirent	*dir_buf;
	t_str			file_path;

	if ((dir_path = opendir(path)) == NULL)
		return NULL;
	file_path = NULL;
	while ((dir_buf = readdir(dir_path)) != NULL)
	{
		if (ft_strequ(cmd, dir_buf->d_name))
		{
			file_path = ft_strmegajoin(3, path, "/", dir_buf->d_name);
			if (file_path == NULL)
				ft_err_mem(TRUE);
			break;
		}
	}
	closedir(dir_path);
	return file_path;
}

t_str			find_cmd_in_env_path(t_rostr cmd, const t_shvars *shvars)
{
	t_rostr	path_val;
	t_str	*paths;
	int		i;
	t_str	result;

	path_val = htab_get_strval(shvars->env, new_hashmem_str("PATH"));
	if (path_val == NULL)
		return NULL;

	if ((paths = ft_strsplit(path_val, ':')) == NULL)
		ft_err_mem(TRUE);

	for (i = 0, result = NULL; result == NULL && paths[i]; i++)
		result = find_cmd_in_specific_path_(paths[i], cmd);

	ft_free_bidimens(paths);
	return result;
}
