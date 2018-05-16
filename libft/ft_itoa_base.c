/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 08:11:26 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/01 14:43:59 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ulen(uintmax_t nbr, int base)
{
	int		i;

	i = 1;
	while (nbr /= base)
		i++;
	return (i);
}

static int	ft_len(intmax_t nbr, int base)
{
	int		i;

	i = 1;
	while (nbr /= base)
		i++;
	return (i);
}

char		*ft_utoa_base(uintmax_t nbr, int base)
{
	uintmax_t	res;
	int			len;
	char		*str;

	len = ft_ulen(nbr, base);
	if (!(str = ft_strnew(len)))
		return (NULL);
	res = nbr % base;
	str[--len] = (res > 9) ? (res - 10) + 'a' : res + '0';
	while (nbr /= base)
	{
		res = nbr % base;
		str[--len] = (res > 9) ? (res - 10) + 'a' : res + '0';
	}
	return (str);
}

char		*ft_itoa_base(intmax_t nbr, int base)
{
	uintmax_t	nb;
	uintmax_t	res;
	int			len;
	char		*str;

	nb = nbr;
	len = ft_len(nbr, base);
	if (nbr < 0 && base == 10)
	{
		nb = -nbr;
		len++;
	}
	if (!(str = ft_strnew(len)))
		return (NULL);
	res = nb % base;
	str[--len] = (res > 9) ? (res - 10) + 'a' : res + '0';
	while (nb /= base)
	{
		res = nb % base;
		str[--len] = (res > 9) ? (res - 10) + 'a' : res + '0';
	}
	if (nbr < 0 && base == 10)
		str[0] = '-';
	return (str);
}
