#ifndef _FT_SIGNALS_H_
# define _FT_SIGNALS_H_

# include <signal.h>

void	ft_sigaction(int signal_code, void (*handler)(int));

#endif