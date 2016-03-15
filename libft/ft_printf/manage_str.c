/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 16:01:43 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/15 17:50:44 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_printf_manage_wchar(char **format, va_list *args, t_data *data)
{
	wchar_t		chr;
	unsigned	len;

	(void)format;
	chr = (wchar_t)va_arg(*args, wint_t);
	len = 0;
	if (chr <= 0x7F)
		len = 1;
	else if (chr <= 0x7FF)
		len = 2;
	else if (chr <= 0xFFFF)
		len = 3;
	else if (chr <= 0x10FFFF)
		len = 4;
	if (data->got_width && !data->right_pad)
		ft_printf_width_pad(len, data->width, data->zero_pad ? '0' : ' ',
				data->fd);
	ft_putwchar_fd(chr, data->fd);
	if (data->got_width && data->right_pad)
		ft_printf_width_pad(len, data->width, data->zero_pad ? '0' : ' ',
				data->fd);
	return (data->got_width ? ft_max(len, data->width) : len);
}

ssize_t	ft_printf_manage_char(char **format, va_list *args, t_data *data)
{
	(void)format;
	if (data->length == 2)
		return (ft_printf_manage_wchar(format, args, data));
	else
	{
		if (data->got_width && !data->right_pad)
			ft_printf_width_pad(1, data->width, data->zero_pad ? '0' : ' ',
					data->fd);
		ft_putchar_fd(va_arg(*args, int), data->fd);
		if (data->got_width && data->right_pad)
			ft_printf_width_pad(1, data->width, ' ', data->fd);
		return (data->got_width ? ft_max(data->width, 1) : 1);
	}
}

ssize_t	ft_printf_manage_str(char **format, va_list *args, t_data *data)
{
	char	*str;
	size_t	strlen;

	if (data->length == 2)
		return (ft_printf_manage_wstr(format, args, data));
	else
	{
		str = va_arg(*args, char*);
		if (!str)
			str = "(null)";
		strlen = data->got_accuracy ? (size_t)(ft_min(ft_strlen(str),
					data->accuracy)) : ft_strlen(str);
		if (data->got_width && !data->right_pad)
			ft_printf_width_pad(strlen, data->width, data->zero_pad ?
					'0' : ' ', data->fd);
		write(data->fd, str, strlen);
		if (data->got_width && data->right_pad)
			ft_printf_width_pad(strlen, data->width, ' ', data->fd);
		return (data->got_width ? ft_max(strlen, data->width) : strlen);
	}
}
