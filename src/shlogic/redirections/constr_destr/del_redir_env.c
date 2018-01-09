#include "shell_redirs_.h"

void		del_redir_env(t_redir_env *redir_env)
{
	ft_memdel((void**)&redir_env->redir_type);
	ft_memdel((void**)&redir_env->next_word_str);
}
