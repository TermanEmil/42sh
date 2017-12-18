/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_process_extra_cmds.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:09:36 by eterman           #+#    #+#             */
/*   Updated: 2016/12/29 11:31:06 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			process_external_argument(char *input, va_list *ap)
{
	char	*aux;

	if (ft_strequ(input, "$"))
	{
		aux = (char*)va_arg(*ap, char*);
		if (aux == NULL)
			return (0);
		ft_strcpy(input, aux);
	}
	return (1);
}

char		*get_extra_cmd_string(char *input, t_data *data, va_list *ap)
{
	char	*result;
	int		what_was_before;

	if (!process_external_argument(input, ap))
		return (NULL);
	what_was_before = data->color_should_clean;
	data->color_should_clean = 1;
	if ((result = get_color(input, ap)))
		return (result);
	if ((result = get_bg_color(input, ap)))
		return (result);
	data->color_should_clean = what_was_before;
	if ((result = get_special_cmds(input, data)))
		return (result);
	return (NULL);
}

/*
**	len_of_buff = -1, because (*format) += len_of_buff + 1 = -1 + 1 == 0
*/

int			process_format_end(t_data *data, char *buff, int *len_of_buff)
{
	*len_of_buff = -1;
	if (data->color_should_clean)
	{
		ft_strcpy(buff, "eoc");
		return (1);
	}
	else
		return (0);
}

void		detect_process_extra_cmds(va_list *ap, t_data *data, CHR **format)
{
	char	buff[50 + 1];
	char	*result;
	int		tmp;
	int		len_of_buff;

	if (**format == 0)
	{
		if (!process_format_end(data, buff, &len_of_buff))
			return ;
	}
	else
	{
		(*format)++;
		if (!substract_cmd(*format, buff, 50))
			return (sprintf_add_data(data, "{", 1));
		len_of_buff = ft_strlen(buff);
	}
	if (!(result = get_extra_cmd_string(buff, data, ap)))
		return (sprintf_add_data(data, "{", 1));
	(*format) += len_of_buff + 1;
	tmp = ft_strlen(result);
	sprintf_add_data(data, result, tmp);
	if (!data->color_count)
		data->not_counted_chars += tmp;
}
