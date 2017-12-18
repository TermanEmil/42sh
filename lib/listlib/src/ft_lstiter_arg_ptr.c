#include "listlib.h"

static void		lstiter_va_lst_f(t_list *lst, int argc, va_list values)
{
	(void)argc;
	va_arg(values, t_liter_arg_void*)(lst, va_arg(values, void*));
}

void			ft_lstiter_arg_ptr(t_list *lst, t_liter_arg_void *f, void *data)
{
	ft_lstiter_arg(lst, &lstiter_va_lst_f, 2, f, data);
}
