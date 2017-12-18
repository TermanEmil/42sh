#ifndef LISTLIB_H
# define LISTLIB_H

# include "libft.h"
# include <stdio.h>
# include <stdarg.h>

/*
** List helpers (defines)
*/

# define LNEXT(list_cell)			((list_cell)->next)
# define LPREV(list_cell)			((list_cell)->prev)
# define LCONT(list_cell, t_type)	((t_type)((list_cell)->content))
# define LSIZE(list_cell)			((list_cell)->content_size)
# define LSTR(list_cell)			LCONT(list_cell, char*)

# define LTONEXT(list_cell)			((list_cell) = LNEXT(list_cell))
# define LTOPREV(list_cell)			((list_cell) = LPREV(list_cell))

# define L_IS_LAST(list_cell)		(LNEXT(list_cell) == NULL)

typedef struct s_list	t_list;

typedef void	(t_ldel_func)(void*, size_t);
typedef void*	(t_lcpy_cont)(void*, size_t);
typedef void	(t_liter_arg)(t_list*, int, va_list);
typedef void	(t_liter_arg_void)(t_list*, void*);

struct			s_list
{
	void		*content;
	size_t		content_size;
	t_list		*next;
	t_list		*prev;
};

// typedef struct	s_lhead
// {
// 	t_list		*list;
// 	t_ldel_func	*del_func;

// }				t_lhead;

/*
** Constr / destr
*/

t_list			*ft_lstnew(void const *content, size_t content_size);
t_list			*ft_lstnew_str(char const *str);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));

/*
** List extremeties adding
*/

void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lst_push_front(t_list **first, t_list *new);

/*
** Get
*/

t_list			*ft_lstget(t_list *head, int index);
t_list			*ft_lst_get_last(t_list *head);
int				ft_lstlen(t_list const *head);
t_list			*ft_lstcpy_one(t_list const *head);
t_list			*ft_lstcpy(t_list const *head);
t_list			*ft_lst_full_cpy(t_list const *head,
					t_lcpy_cont *cpy_f, t_ldel_func *del_f);

/*
** Insert
*/

int				ft_lstinsert(t_list **head, size_t i,
					t_list *target, t_list *prev);
int				ft_lst_insert_range(t_list **head, size_t i, t_list *elements);

/*
** Remove
*/

void			ft_lstpop_front(t_list ** head, t_ldel_func * del);
void			ft_lstpop_back(t_list ** head, t_ldel_func * del);
void			ft_lstrm(t_list **h, t_list *trget, t_ldel_func *del);
int				ft_lstrm_at(t_list **head, size_t index, t_ldel_func *del);

/*
** Iterating functions
*/

void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lst_rev_iter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstiter_arg(t_list *lst, t_liter_arg *f, int argc, ...);
void			ft_lstiter_arg_ptr(t_list *lst,
					t_liter_arg_void *f, void *data);
/*
** Miscellaneous
*/

void			ft_lstreverse(t_list **head);

/*
** Sorting
*/

void			ft_lst_merge_sort(t_list **head, int (*f)(void*, void*));

/*
** List helpers
*/

void			ft_lstprint_str(t_list const * elem);

#endif