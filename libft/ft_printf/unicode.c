/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 11:25:15 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/20 19:34:27 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks for the size in bits of the argument
**
** Return : The size in bits
*/

static int	ft_bitlen(unsigned int n)
{
	unsigned int	c;

	c = 0;
	while (n)
	{
		c++;
		n >>= 1;
	}
	return (c);
}

/*
** Checks for the size in Bytes of the argument
**
** Return : The size in Bytes
*/

int			ft_bytelen(wchar_t arg)
{
	int		bitlen;

	if (arg >= 0xD800 && arg <= 0xDFFF)
		return (-1);
	if (arg > 0x10FFFF)
		return (-1);
	bitlen = ft_bitlen(arg);
	if (bitlen <= 7)
		return (1);
	else if (bitlen <= 11)
		return (2);
	else if (bitlen <= 16)
		return (3);
	else if (bitlen <= 21)
		return (4);
	return (-1);
}

/*
** Applies unicode masks to the argument according to the size in Bytes
**
** Return : The number of Bytes
*/

int			unicode_mask_applier(char *byte, wchar_t arg)
{
	int		bytelen;

	bytelen = ft_bytelen(arg);
	if (bytelen == 1)
		byte[0] = arg;
	else if (bytelen == 2)
	{
		byte[0] = 0xC0 | (arg >> 6 & 0x1F);
		byte[1] = 0x80 | (arg & 0x3F);
	}
	else if (bytelen == 3)
	{
		byte[0] = 0xE0 | (arg >> 12 & 0x0F);
		byte[1] = 0x80 | (arg >> 6 & 0x3F);
		byte[2] = 0x80 | (arg & 0x3F);
	}
	else if (bytelen == 4)
	{
		byte[0] = 0xF0 | (arg >> 18 & 0x07);
		byte[1] = 0x80 | (arg >> 12 & 0x3F);
		byte[2] = 0x80 | (arg >> 6 & 0x3F);
		byte[3] = 0x80 | (arg & 0x3F);
	}
	return (bytelen);
}
