#include "shinput.h"

/*
** Add a copy of the given key to the lst.
*/

void	add_cpykey_to_list(t_lst_inkey **lst, const t_sh_inkey *sh_inkey)
{
	t_sh_inkey buf_key;

	buf_key = sh_inkey_cpy_construct(sh_inkey);
	ft_lstadd(lst, ft_lstnew(&buf_key, sizeof(buf_key)));
}
