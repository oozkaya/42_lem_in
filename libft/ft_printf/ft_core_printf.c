/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:22:31 by oozkaya           #+#    #+#             */
/*   Updated: 2018/03/20 15:30:51 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Does a parsing to get the right function according to the conversion given
**
** Return : If successful, returns '1'
** 			If not, returns '-1'
*/

static int	function_parser(t_buffer *buf, t_format *fmt, va_list ap)
{
	int					i;
	static const t_conv	tab_conv[] = {{ "di", d_arg },
		{ "buo", u_o_arg },
		{ "pxX", p_x_arg },
		{ "c", c_arg },
		{ "s", s_arg },
		{ "C", wc_arg },
		{ "S", ws_arg },
		{ "%", pct_arg },
		{ NULL, NULL }
	};

	i = 0;
	while (tab_conv[i].conversion)
	{
		if (ft_strchr(tab_conv[i].conversion, fmt->conv))
			return (tab_conv[i].arg(buf, fmt, ap));
		i++;
	}
	return (-1);
}

/*
** Parses the "format" to check all the existing fields (flags, width, etc...)
**
** Return : The "format" left after the parsing
*/

static char	*parse_all(char *format, t_format *fmt, va_list ap)
{
	if (*format == '\0')
		return (format);
	format = flags_parser(format, fmt);
	format = width_parser(format, fmt, ap);
	format = precision_parser(format, fmt, ap);
	format = type_size_parser(format, fmt);
	if (conv_parser(*format, fmt) == 0)
		return (format);
	return (format + 1);
}

/*
** Main function serving all the other "ft_printf and cie" functions
** Parses the "format" with the functions above and the color functions
**
** Return : If successful, returns the buffer len at the end
** 			If not, returns '-1'
*/

int			ft_core_printf(t_buffer *buf, char *format, va_list ap)
{
	t_format	fmt;
	char		*conv;

	while ((conv = ft_strchr(format, '%')) != NULL)
	{
		ft_bzero(&fmt, sizeof(fmt));
		buffer_add_str(buf, format, conv - format);
		format = parse_all(conv + 1, &fmt, ap);
		if (fmt.conv != '\0')
		{
			if (function_parser(buf, &fmt, ap) == -1)
			{
				ft_memdel((void**)&buf->str);
				return (-1);
			}
		}
	}
	if (*format != '\0')
		buffer_add_str(buf, format, ft_strlen(format));
	return (buf->len);
}
