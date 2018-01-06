#ifndef _SHELL42_UTILS_H_
# define _SHELL42_UTILS_H_

# include <regex.h>
# include "libft.h"

void	regex_proj_error(const regex_t *regex_patern, int errcode, int index);
t_bool	regex_mini_match(t_rostr patern, t_rostr str);

#endif