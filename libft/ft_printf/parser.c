/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:23:43 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/23 17:22:08 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Parses the "format" to check all the existing flags (' ', '0', '+', '-', '#')
**
** Return : The "format" left after the parsing
*/

char	*flags_parser(char *format, t_format *fmt)
{
	char	c;

	c = *format;
	while (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
	{
		if (c == '#')
			fmt->hashtag = 1;
		else if (c == '0')
			fmt->zero = 1;
		else if (c == '-')
			fmt->minus = 1;
		else if (c == ' ')
			fmt->space = 1;
		else if (c == '+')
			fmt->plus = 1;
		c = *++format;
	}
	return (format);
}

/*
** Parses the "format" to check the width field
**
** Return : The "format" left after the parsing
*/

char	*width_parser(char *format, t_format *fmt, va_list ap)
{
	while (ft_isdigit(*format) || *format == '*')
	{
		if (ft_isdigit(*format))
			fmt->width = 0;
		while (ft_isdigit(*format))
		{
			fmt->width = fmt->width * 10 + (*format - '0');
			format++;
		}
		if (*format == '*')
		{
			if ((fmt->width = va_arg(ap, int)) < 0)
			{
				fmt->minus = 1;
				fmt->width = -(fmt->width);
			}
			format++;
		}
	}
	return (format);
}

/*
** Parses the "format" to check the precision field
**
** Return : The "format" left after the parsing
*/

char	*precision_parser(char *format, t_format *fmt, va_list ap)
{
	char	c;

	if (format[0] == '.' && format[1] == '*')
	{
		fmt->prec = va_arg(ap, int);
		format += 2;
		fmt->prec_activated = 1;
		return (format);
	}
	c = *format;
	if (c == '.')
	{
		c = *++format;
		while (ft_isdigit(c))
		{
			fmt->prec = fmt->prec * 10 + (c - '0');
			c = *++format;
			fmt->prec_activated = 1;
		}
		fmt->prec_dot_activated = 1;
	}
	return (format);
}

/*
** Parses the "format" to check the type size
**
** Return : The "format" left after the parsing
*/

char	*type_size_parser(char *format, t_format *fmt)
{
	char	c;

	c = *format;
	if (c != 'h' && c != 'l' && c != 'j' && c != 'z')
		return (format);
	if (c == 'h' && format[1] == 'h')
	{
		fmt->type_size = 'H';
		format += 2;
	}
	else if (c == 'l' && format[1] == 'l')
	{
		fmt->type_size = 'L';
		format += 2;
	}
	else
	{
		fmt->type_size = c;
		format += 1;
	}
	return (format);
}

/*
** Parses the "format" to check the conversion field
**
** Return : If successful, returns the conversion
** 			If not, returns '0'
*/

int		conv_parser(char c, t_format *fmt)
{
	if (c == 'd' || c == 'i')
		fmt->conv = 'd';
	else if (c == 'c' || c == 's' || c == 'S' || c == 'C' || c == '%')
		fmt->conv = c;
	else if (c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == 'p')
		fmt->conv = c;
	else if (c == 'b')
		fmt->conv = c;
	else if (c == 'D' || c == 'O' || c == 'U')
	{
		fmt->type_size = 'L';
		fmt->conv = c + 32;
	}
	else if (c != 0)
	{
		fmt->conv = 'c';
		fmt->no_conv = c;
	}
	return (fmt->conv);
}
