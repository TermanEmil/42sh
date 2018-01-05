#include "shlogic.h"

t_bool	cmd_is_specific_program(t_rostr cmd)
{
	return cmd[0] != '\0' && ft_strchr("./", cmd[0]) != NULL;
}
