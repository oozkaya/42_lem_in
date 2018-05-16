/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoinfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 08:48:07 by oozkaya           #+#    #+#             */
/*   Updated: 2017/12/14 12:10:19 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoinfree(char const *s1, char const *s2, size_t len, int pick)
{
	char	*join;

	if (pick < 0 || pick > 2)
		return (NULL);
	join = ft_strnjoin(s1, s2, len);
	if (pick == 0 || pick == 2)
		ft_memdel((void**)&s1);
	if (pick == 1 || pick == 2)
		ft_memdel((void**)&s2);
	return (join);
}
