#include "shlogic.h"

t_exec_cmd_f	*get_sh_builtin_f(t_rostr cmd, const t_hashtab *built_in_cmds)
{
	t_hashmem	htab_match;

	if (cmd == NULL)
		return NULL;

	htab_match = htab_get_val(built_in_cmds, new_hashmem_str((t_str)cmd));

	if (htab_match.mem == NULL)
		return NULL;
	else
		return htab_match.mem;
}
