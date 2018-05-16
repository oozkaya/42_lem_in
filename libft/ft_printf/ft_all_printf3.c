/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_printf3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:36:13 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/23 12:07:06 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Exact analogs of ft_printf and ft_vprintf,
** except that they write to an already malloced string "str"
**
** Return : Same as ft_printf
*/

int		ft_sprintf(char *str, const char *format, ...)
{
	t_buffer	buf;
	int			ret;
	va_list		ap;

	buffer_init(&buf);
	va_start(ap, format);
	if ((ret = ft_core_printf(&buf, (char *)format, ap)) < 0)
		return (-1);
	va_end(ap);
	ft_memmove(str, buf.str, ft_strlen(buf.str));
	ft_memdel((void **)&buf.str);
	return (ret - buf.clr_len);
}

int		ft_vsprintf(char *str, const char *format, va_list ap)
{
	t_buffer	buf;
	int			ret;

	buffer_init(&buf);
	if ((ret = ft_core_printf(&buf, (char *)format, ap)) < 0)
		return (-1);
	ft_memmove(str, buf.str, ft_strlen(buf.str));
	ft_memdel((void **)&buf.str);
	return (ret - buf.clr_len);
}

/*
** Same as above, except they write at most "size" bytes
** (including the terminating null byte ('\0')) to "str"
*/

int		ft_snprintf(char *str, size_t size, const char *format, ...)
{
	t_buffer	buf;
	int			ret;
	va_list		ap;

	buffer_init(&buf);
	va_start(ap, format);
	if ((ret = ft_core_printf(&buf, (char *)format, ap)) < 0)
		return (-1);
	va_end(ap);
	ft_memmove(str, buf.str, size - 1);
	ft_memdel((void **)&buf.str);
	return (ret - buf.clr_len);
}

int		ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	t_buffer	buf;
	int			ret;

	buffer_init(&buf);
	if ((ret = ft_core_printf(&buf, (char *)format, ap)) < 0)
		return (-1);
	ft_memmove(str, buf.str, size - 1);
	ft_memdel((void **)&buf.str);
	return (ret - buf.clr_len);
}
