/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_c_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:18:48 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/20 19:43:47 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handles all the possible fields for the conversion %c
**
** Return : Always '1' if successful
*/

int		c_arg(t_buffer *buf, t_format *fmt, va_list ap)
{
	char	arg;
	char	fill;
	int		size;

	if (fmt->type_size == 'l')
		return (wc_arg(buf, fmt, ap));
	arg = va_arg(ap, int);
	fill = (fmt->zero && !fmt->minus) ? '0' : ' ';
	size = fmt->width ? fmt->width - 1 : 0;
	if (!fmt->minus)
		buffer_add_char(buf, fill, size);
	if (fmt->no_conv)
		buffer_add_char(buf, fmt->no_conv, 1);
	else
		buffer_add_char(buf, arg, 1);
	if (fmt->minus)
		buffer_add_char(buf, fill, size);
	return (1);
}

/*
** Handles all the possible fields for the conversion %C
**
** Return : If successful, returns '1'
** 			If not, returns '-1'
*/

int		wc_arg(t_buffer *buf, t_format *fmt, va_list ap)
{
	wchar_t	arg;
	char	*bytes;
	char	fill;
	int		size;
	int		bytes_len;

	arg = va_arg(ap, wchar_t);
	if (!(bytes = (char*)malloc(sizeof(char) * 5)))
		return (-1);
	if ((bytes_len = unicode_mask_applier(bytes, arg)) == -1)
	{
		ft_memdel((void**)&bytes);
		return (-1);
	}
	fill = (fmt->zero && !fmt->minus) ? '0' : ' ';
	size = (fmt->width - bytes_len) > 0 ? fmt->width - bytes_len : 0;
	if (!fmt->minus)
		buffer_add_char(buf, fill, size);
	buffer_add_str(buf, bytes, bytes_len);
	if (fmt->minus)
		buffer_add_char(buf, fill, size);
	ft_memdel((void**)&bytes);
	return (1);
}

/*
** Handles all the possible fields for the conversion %%
**
** Return : Always '1' if successful
*/

int		pct_arg(t_buffer *buf, t_format *fmt, va_list ap)
{
	int		size;
	char	fill;

	fill = (fmt->zero && !fmt->minus) ? '0' : ' ';
	size = fmt->width ? fmt->width - 1 : 0;
	(void)ap;
	if (!fmt->minus)
		buffer_add_char(buf, fill, size);
	buffer_add_char(buf, '%', 1);
	if (fmt->minus)
		buffer_add_char(buf, fill, size);
	return (1);
}
