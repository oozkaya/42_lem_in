/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_printf2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 22:03:43 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/23 12:08:02 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Exact analogs of ft_printf and ft_vprintf,
** except that they write to a string "str" that they malloc
**
** Return : Same as ft_printf
*/

int		ft_asprintf(char **str, const char *format, ...)
{
	t_buffer	buf;
	int			ret;
	va_list		ap;

	buffer_init(&buf);
	va_start(ap, format);
	if ((ret = ft_core_printf(&buf, (char *)format, ap)) < 0)
		return (-1);
	va_end(ap);
	if (!(*str = ft_strdup(buf.str)))
		return (-1);
	ft_memdel((void **)&buf.str);
	return (ret - buf.clr_len);
}

int		ft_vasprintf(char **str, const char *format, va_list ap)
{
	t_buffer	buf;
	int			ret;

	buffer_init(&buf);
	if ((ret = ft_core_printf(&buf, (char *)format, ap)) < 0)
		return (-1);
	if (!(*str = ft_strdup(buf.str)))
		return (-1);
	ft_memdel((void **)&buf.str);
	return (ret - buf.clr_len);
}
