#include "libft.h"
#include "eventlib.h"
#include <ft_printf.h>

void	ft_error(int const exit_program, char const *format, ...)
{
	va_list		ap;
	t_data		*data;

	va_start(ap, format);
	data = sprintf_new_data();
	process_format(format, &ap, data);
	va_end(ap);
	if (data->str)
	{
		write(STDERR_FILENO, data->str, data->printed_chars);
		free(data->str);
	}
	free(data);
	if (exit_program)
		event_exit(EXIT_FAILURE);
}