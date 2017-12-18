#include "listlib.h"

void	ft_lstiter_arg(t_list *lst, t_liter_arg *f, int argc, ...)
{
	va_list	ap;
	va_list	passed;

	va_start(ap, argc);
	while (lst)
	{
		va_copy(passed, ap);
		f(lst, argc, passed);
		va_end(passed);

		LTONEXT(lst);
	}
	va_end(ap);
}
