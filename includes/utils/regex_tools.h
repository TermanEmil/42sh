#ifndef _REGEX_TOOLS_H_
# define _REGEX_TOOLS_H_

# include <regex.h>
# include "libft.h"

regmatch_t	regex_mini_get_regmatch(t_rostr patern, t_rostr str);
t_bool		regex_mini_match(t_rostr patern, t_rostr str);
t_str		regex_get_match(t_rostr patern, t_rostr str);

void		regex_proj_error(const regex_t *regex_patern, int errcode, int i);

#endif