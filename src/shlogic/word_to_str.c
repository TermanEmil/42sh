#include "shlogic.h"

t_str	word_to_str(const t_lst_inkey *keys)
{
	return ft_lst_join(
		(void*)keys,
		(t_rostr (*)(const void*, size_t))&sh_inkey_get_meaning, NULL);
}
