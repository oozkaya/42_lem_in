/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_s_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:18:36 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/20 21:36:09 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handles the conversion %S buffer filling process
**
** Return : void
*/

static void	ws_buffer_add(t_buffer *buf, t_format *fmt, char *str)
{
	int		size;
	char	fill;

	fill = (fmt->zero && !fmt->minus) ? '0' : ' ';
	size = fmt->width ? fmt->width - ft_strlen(str) : 0;
	size = (size < 0) ? 0 : size;
	if (!fmt->minus)
		buffer_add_char(buf, fill, size);
	buffer_add_str(buf, str, ft_strlen(str));
	if (fmt->minus)
		buffer_add_char(buf, fill, size);
	ft_memdel((void**)&str);
}

/*
** Handles the unicode process for the conversion %S
**
** Return : If successful, returns '1'
** 			If not, returns '-1'
*/

static int	ws_arg_unicode(char *bytes, wchar_t *arg, char *str, t_format *fmt)
{
	int		index;
	int		total;
	int		tmp;

	index = 0;
	tmp = 0;
	while (*arg != L'\0')
	{
		if ((total = unicode_mask_applier(bytes, *arg)) == -1)
			return (-1);
		tmp += total;
		if ((fmt->prec < tmp) && fmt->prec_dot_activated)
			break ;
		ft_memmove(str + index, bytes, total);
		index += total;
		arg++;
	}
	str[index] = '\0';
	ft_memdel((void**)&bytes);
	return (1);
}

/*
** Handles all the possible fields for the conversion %S
**
** Return : If successful, returns '1'
** 			If not, returns '-1'
*/

int			ws_arg(t_buffer *buf, t_format *fmt, va_list ap)
{
	wchar_t	*arg;
	char	*bytes;
	char	*str;

	if ((arg = va_arg(ap, wchar_t*)) == 0)
		arg = L"(null)";
	if (!(bytes = (char *)malloc(sizeof(char) * 4 + 1)))
		return (-1);
	if (!(str = (char *)malloc(sizeof(wchar_t) * ft_wslen(arg) + 1)))
		return (-1);
	if (ws_arg_unicode(bytes, arg, str, fmt) == -1)
		return (-1);
	ws_buffer_add(buf, fmt, str);
	return (1);
}

/*
** Handles the conversion %s buffer filling process
**
** Return : void
*/

static void	s_buffer_add(t_buffer *buf, t_format *fmt, char *str, char *arg)
{
	int		index;
	char	fill;
	int		size;

	fill = (fmt->zero && !fmt->minus) ? '0' : ' ';
	index = 0;
	while (*arg != '\0')
	{
		if (fmt->prec == index && fmt->prec_activated)
			break ;
		ft_memmove(str + index, arg, 1);
		index++;
		arg++;
	}
	str[index] = '\0';
	size = fmt->width ? fmt->width - ft_strlen(str) : 0;
	if (fmt->prec_dot_activated && !fmt->prec_activated && fmt->width)
		size += ft_strlen(str);
	size = (size < 0) ? 0 : size;
	if (!fmt->minus)
		buffer_add_char(buf, fill, size);
	if (!(fmt->prec_dot_activated && !fmt->prec_activated && fmt->width))
		buffer_add_str(buf, str, ft_strlen(str));
	if (fmt->minus)
		buffer_add_char(buf, fill, size);
}

/*
** Handles all the possible fields for the conversion %s
**
** Return : If successful, returns '1'
** 			If not, returns '-1'
*/

int			s_arg(t_buffer *buf, t_format *fmt, va_list ap)
{
	char	*arg;
	char	*str;

	if (fmt->type_size == 'l')
		return (ws_arg(buf, fmt, ap));
	if (fmt->prec_dot_activated && !fmt->prec_activated && !fmt->width)
		return (1);
	if ((arg = va_arg(ap, char *)) == 0)
		arg = "(null)";
	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(arg) + 1)))
		return (-1);
	s_buffer_add(buf, fmt, str, arg);
	ft_memdel((void**)&str);
	return (1);
}
