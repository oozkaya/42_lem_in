/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:21:54 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/20 19:43:02 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks for the right argument according to the type size
**
** Return : The argument
*/

static char	*type_size_apply(t_format *fmt, va_list ap)
{
	char		*arg;
	intmax_t	n;

	fmt->hashtag = 0;
	if (fmt->type_size == 'h')
		n = (short int)va_arg(ap, int);
	else if (fmt->type_size == 'H')
		n = (char)va_arg(ap, int);
	else if (fmt->type_size == 'l')
		n = va_arg(ap, long int);
	else if (fmt->type_size == 'L')
		n = va_arg(ap, long long int);
	else if (fmt->type_size == 'j')
		n = va_arg(ap, intmax_t);
	else if (fmt->type_size == 'z')
		n = va_arg(ap, size_t);
	else
		n = va_arg(ap, int);
	arg = ft_itoa_base(n, 10);
	return (arg);
}

/*
** Handles all the fields (flags, width, precision) for the conversion %d
**
** Return : Always '1' if successful
*/

int			d_arg(t_buffer *buf, t_format *fmt, va_list ap)
{
	char	*arg;
	char	fill;
	int		check;
	int		size;

	check = 0;
	arg = type_size_apply(fmt, ap);
	check_prec(&check, fmt, arg);
	fill = (fmt->zero && !fmt->minus) ? '0' : ' ';
	size = int_arg_filling_size(fmt, arg);
	if (fmt->zero)
		int_arg_sign(buf, fmt, arg);
	if (!fmt->minus)
		buffer_add_char(buf, fill, size);
	if (!fmt->zero)
		int_arg_sign(buf, fmt, arg);
	add_prec(buf, fmt, arg, size);
	if (arg[0] == '-')
		buffer_add_str(buf, arg + 1, check = (check) ? 0 : ft_strlen(arg + 1));
	else
		buffer_add_str(buf, arg, check = (check) ? 0 : ft_strlen(arg));
	if (fmt->minus)
		buffer_add_char(buf, fill, size);
	ft_memdel((void**)&arg);
	return (1);
}
