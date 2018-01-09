#include "shlogic.h"

void	dup_and_closelst(const t_lst_to_dup *lst_to_dup, t_bool close_it)
{
	const t_to_dup	*to_dup;

	for (; lst_to_dup; LTONEXT(lst_to_dup))
	{
		to_dup = LCONT(lst_to_dup, t_to_dup*);
		if (to_dup->to_close)
		{
			TMP_FAIL_RETRY(close(to_dup->fd));
			errno = 0;
		}
		else
			dup_and_close(to_dup->fd, to_dup->default_fd, close_it);
	}
}
