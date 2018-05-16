/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_x_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:21:03 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/23 18:25:27 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks for the right argument and applies the right flags
**
** Return : The argument
*/

static char	*arg_checker(uintmax_t n, t_format *fmt)
{
	char	*arg;

	fmt->plus = 0;
	fmt->space = 0;
	if (fmt->conv == 'p')
		fmt->hashtag = 1;
	arg = ft_utoa_base(n, 16);
	if (fmt->conv == 'X')
		arg = ft_strupr(arg);
	return (arg);
}

/*
** Checks for the right argument according to the type size
**
** Return : The argument
*/

static char	*type_size_apply(t_format *fmt, va_list ap)
{
	char		*arg;
	uintmax_t	n;

	if (fmt->conv == 'p')
		n = (uintmax_t)va_arg(ap, void*);
	else if (fmt->type_size == 'h')
		n = (unsigned short int)va_arg(ap, int);
	else if (fmt->type_size == 'H')
		n = (unsigned char)va_arg(ap, int);
	else if (fmt->type_size == 'l')
		n = va_arg(ap, unsigned long int);
	else if (fmt->type_size == 'L')
		n = va_arg(ap, unsigned long long int);
	else if (fmt->type_size == 'j')
		n = va_arg(ap, uintmax_t);
	else if (fmt->type_size == 'z')
		n = va_arg(ap, size_t);
	else
		n = va_arg(ap, unsigned int);
	arg = arg_checker(n, fmt);
	return (arg);
}

/*
** Resizes the filling size according to the fields
**
** Return : The resized size
*/

static int	p_x_arg_resizer(int *check, t_format *fmt, char *arg)
{
	int		size;

	if (fmt->prec >= 0 && fmt->prec_dot_activated)
		fmt->zero = 0;
	if (fmt->prec == 0 && fmt->prec_dot_activated == 1
			&& ft_strequ(arg, "0") && !fmt->plus)
	{
		*check = 1;
		fmt->width++;
	}
	size = int_arg_filling_size(fmt, arg);
	if (fmt->conv == 'p')
		fmt->hashtag = fmt->hashtag * 2;
	else
		fmt->hashtag = (ft_strequ(arg, "0") ? 0 : fmt->hashtag * 2);
	fmt->tmp = size;
	size = size - fmt->hashtag;
	size = (size < 0) ? 0 : size;
	return (size);
}

/*
** Handles all the fields (flags, width, precision) for the conversion %p and %x
**
** Return : Always '1' if successful
*/

int			p_x_arg(t_buffer *buf, t_format *fmt, va_list ap)
{
	char	*arg;
	char	fill;
	int		check;
	int		size;

	check = 0;
	arg = type_size_apply(fmt, ap);
	size = p_x_arg_resizer(&check, fmt, arg);
	fill = (fmt->zero && !fmt->minus) ? '0' : ' ';
	if (!fmt->minus && !fmt->zero)
		buffer_add_char(buf, fill, size);
	if (fmt->hashtag)
		buffer_add_str(buf, (fmt->conv == 'X') ? "0X" : "0x", 2);
	if (!fmt->minus && fmt->zero)
		buffer_add_char(buf, fill, size);
	add_prec(buf, fmt, arg, size);
	buffer_add_str(buf, arg, check = (check) ? 0 : ft_strlen(arg));
	if (fmt->minus)
		buffer_add_char(buf, fill, size);
	ft_memdel((void**)&arg);
	return (1);
}
