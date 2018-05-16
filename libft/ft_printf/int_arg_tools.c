/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_arg_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:22:48 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/20 18:58:42 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks all the conditions related to the precision field
**
** Return : void
*/

void	check_prec(int *check, t_format *fmt, char *arg)
{
	if (fmt->prec >= 0 && fmt->prec_dot_activated)
		fmt->zero = 0;
	if (fmt->prec == 0 && fmt->prec_dot_activated == 1
			&& ft_strequ(arg, "0") && !fmt->hashtag)
	{
		*check = 1;
		fmt->width++;
	}
	if (fmt->prec == 2 && ft_strlen(arg) == 2 && arg[0] == '-')
		fmt->tmp2 = 1;
	if (fmt->prec == fmt->width && fmt->prec_activated)
		fmt->tmp3 = 1;
}

/*
** Applies all the conditions related to the precision field
** Usually adds zeros according to the argument and the fields
**
** Return : void
*/

void	add_prec(t_buffer *buf, t_format *fmt, char *arg, int size)
{
	int		sign;
	int		minus;
	int		len;
	int		total;
	int		size2;

	len = ft_strlen(arg);
	minus = (arg[0] == '-') ? 1 : 0;
	if ((fmt->prec > 0 && fmt->width <= 0) || (fmt->prec == 0 && fmt->tmp2))
	{
		buffer_add_char(buf, '0', fmt->prec + minus);
		return ;
	}
	sign = (fmt->plus || fmt->space) ? 1 : 0;
	total = fmt->prec + len + size + sign;
	size2 = (fmt->width - len) > 0 ? fmt->width - len : 0;
	if (fmt->prec > 0 && (total + fmt->hashtag - minus == fmt->width
		|| total + fmt->hashtag == fmt->width || total == fmt->width
		|| total + fmt->tmp == fmt->width || total - sign == fmt->width
		|| total - sign - minus == fmt->width))
		buffer_add_char(buf, '0', fmt->prec);
	else if (fmt->tmp3 && fmt->prec == 0)
		buffer_add_char(buf, '0', size2);
}

/*
** Handles the argument sign
**
** Return : void
*/

void	int_arg_sign(t_buffer *buf, t_format *fmt, char *arg)
{
	char	sign;

	sign = (fmt->plus) ? '+' : ' ';
	if (arg[0] == '-')
		buffer_add_char(buf, '-', 1);
	else if (fmt->plus || fmt->space)
		buffer_add_char(buf, sign, 1);
}

/*
** Calculates the filling size (with zeros or spaces) according to the fields
**
** Return : The filling size
*/

int		int_arg_filling_size(t_format *fmt, char *arg)
{
	int		len;
	int		sign;
	int		size;
	int		size2;

	len = ft_strlen(arg);
	if (fmt->prec > fmt->width)
	{
		fmt->prec = (fmt->prec - len) > 0 ? fmt->prec - len : 0;
		fmt->width = 0;
		return (0);
	}
	sign = (fmt->plus || fmt->space) ? 1 : 0;
	if (arg[0] == '-')
		fmt->prec = (fmt->prec) ? fmt->prec - len + 1 : 0;
	else
		fmt->prec = (fmt->prec) ? fmt->prec - len : 0;
	if (fmt->prec < 0)
		fmt->prec = 0;
	size = (fmt->width > len) ? fmt->width - fmt->prec : len - fmt->prec;
	size2 = ((size - sign - len) < 0) ? 0 : size - sign - len;
	if (arg[0] == '-')
		return ((size - len) >= 0 ? size - len : 0);
	else
		return (size2);
}
