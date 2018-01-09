#include "shell42.h"

void		shdata_destruct(t_shdata * const target)
{
	if (target)
	{
		shinput_destruct(&target->input);
		
		shvars_destroy(&target->shvars);
		del_hashtab(&target->built_in_cmds);
		del_hashtab(&g_shinput->key_cmds);
		
		TMP_FAIL_RETRY(close(STDIN_FILENO));
		TMP_FAIL_RETRY(close(STDOUT_FILENO));
		TMP_FAIL_RETRY(close(STDERR_FILENO));
	}
}
