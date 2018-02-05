#include "ft_printf.h"
#include <pthread.h>

int		sync_printf(pthread_mutex_t *mutex, int fd, t_rostr format, ...)
{
	va_list		ap;
	t_data		*data;

	va_start(ap, format);
	pthread_mutex_lock(mutex);
	data = sprintf_new_data();
	process_format(format, &ap, data);
	va_end(ap);

	if (data->str)
	{
		write(fd, data->str, data->printed_chars);
		free(data->str);
	}
	free(data);
	pthread_mutex_unlock(mutex);
	return 0;
}