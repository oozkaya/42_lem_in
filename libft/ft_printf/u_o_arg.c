/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_o_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:21:32 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/20 19:46:24 by oozkaya          ###   ########.fr       */
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
	if (fmt->conv == 'u' || fmt->conv == 'b')
	{
		fmt->hashtag = 0;
		arg = (fmt->conv == 'u') ? ft_utoa_base(n, 10) : ft_utoa_base(n, 2);
	}
	else
		arg = ft_utoa_base(n, 8);
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

	if (fmt->type_size == 'h')
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

static void	u_o_arg_resizer(int *size1, int *size2, t_format *fmt, char *arg)
{
	int		tmp;

	*size1 = int_arg_filling_size(fmt, arg);
	tmp = *size1;
	fmt->hashtag = (ft_strequ(arg, "0") ? 0 : fmt->hashtag);
	*size1 = *size1 - fmt->hashtag;
	*size1 = (*size1 < 0) ? 0 : *size1;
	if (fmt->prec && tmp + fmt->hashtag + (int)ft_strlen(arg)
			+ fmt->prec != fmt->width)
		*size2 = (*size1 == 0) ? 0 : *size1 + fmt->hashtag;
	else
		*size2 = *size1;
}

/*
** Handles all the fields (flags, width, precision) for the conversion %u and %o
**
** Return : Always '1' if successful
*/

int			u_o_arg(t_buffer *buf, t_format *fmt, va_list ap)
{
	char	*arg;
	char	fill;
	int		check;
	int		size1;
	int		size2;

	size1 = 0;
	size2 = 0;
	check = 0;
	arg = type_size_apply(fmt, ap);
	check_prec(&check, fmt, arg);
	fill = (fmt->zero && !fmt->minus) ? '0' : ' ';
	u_o_arg_resizer(&size1, &size2, fmt, arg);
	if (!fmt->minus)
		buffer_add_char(buf, fill, size2);
	if (fmt->hashtag && !fmt->prec)
		buffer_add_char(buf, '0', 1);
	add_prec(buf, fmt, arg, size1);
	buffer_add_str(buf, arg, check = (check) ? 0 : ft_strlen(arg));
	if (fmt->minus)
		buffer_add_char(buf, fill, size2);
	ft_memdel((void**)&arg);
	return (1);
}
