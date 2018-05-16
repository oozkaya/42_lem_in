/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 20:29:32 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/11 14:58:53 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strend(const char *s, const char *t)
{
	size_t ls;
	size_t lt;

	ls = ft_strlen(s);
	lt = ft_strlen(t);
	if (ls >= lt)
		return (0 == ft_memcmp(t, s + (ls - lt), lt));
	return (0);
}
