#include "ft_printf/ft_printf.h"
#include "termlib.h"

/*
** It's like printf, but you can choose where on the screen to print.
*/

int		term_printf(int x, int y, char const *format, ...)
{
	va_list		ap;
	int			result;
	t_data		*data;


	term_save_cursor_pos();
	if (x < 0 || y < 0)
	{
		term_cursor_goto_home();
		term_clear_from_cursor_to_end_line();
	}
	else
	{
		term_cursor_goto(0, y);
		term_clear_from_cursor_to_end_line();
		term_cursor_goto(x, y);
	}

	va_start(ap, format);
	data = sprintf_new_data();
	process_format(format, &ap, data);
	va_end(ap);
	result = data->printed_chars - data->not_counted_chars;
	if (data->str)
	{
		write(1, data->str, data->printed_chars);
		free(data->str);
	}
	free(data);
	term_restore_cursor_pos();
	return (result);
}
