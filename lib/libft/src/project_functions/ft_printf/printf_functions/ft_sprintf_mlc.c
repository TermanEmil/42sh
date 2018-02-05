#include "ft_printf.h"

int				ft_sprintf_mlc(char **buff, const char *format, ...)
{
	va_list		ap;
	int			result;
	t_data		*data;

	data = sprintf_new_data();
	va_start(ap, format);
	process_format(format, &ap, data);
	va_end(ap);
	result = data->printed_chars - data->not_counted_chars;
	*buff = data->str;
	free(data);
	return (result);
}
