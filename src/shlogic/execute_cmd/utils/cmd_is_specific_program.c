#include "shlogic.h"

t_bool	cmd_is_specific_program(t_rostr cmd)
{
	if (cmd == NULL)
		return FALSE;
	return cmd[0] != '\0' && ft_strchr("./", cmd[0]) != NULL;
}
