/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:03:15 by oozkaya           #+#    #+#             */
/*   Updated: 2017/11/15 13:29:19 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	char	*s1;
	char	*s1_begin;
	char	*s2;

	if (!*to_find)
		return ((char *)str);
	s1 = (char *)str;
	while (*s1)
	{
		s1_begin = s1;
		s2 = (char *)to_find;
		while (*s1 && *s2 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		if (!*s2)
			return (s1_begin);
		s1 = s1_begin + 1;
	}
	return (NULL);
}
