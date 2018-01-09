#include "ft_signals.h"
#include "libft.h"
#include "ft_errors.h"

void	ft_sigaction(int signal_code, void (*handler)(int))
{
	struct sigaction	handler_data;

	ft_bzero(&handler_data, sizeof(handler_data));
	handler_data.sa_handler = handler;
	if (sigaction(signal_code, &handler_data, NULL) == -1)
		ft_error(TRUE, "%s: Can't listen to signal %d\n",
			g_proj_name, signal_code);
}
