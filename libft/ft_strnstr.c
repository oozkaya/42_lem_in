/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:15:08 by oozkaya           #+#    #+#             */
/*   Updated: 2017/11/22 09:37:34 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	size;

	if (!*to_find)
		return ((char *)str);
	size = ft_strlen(to_find);
	while (*str && len-- >= size)
	{
		if (*str == *to_find && ft_strncmp(str, to_find, size) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
