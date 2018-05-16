/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:16:58 by oozkaya           #+#    #+#             */
/*   Updated: 2017/11/20 10:23:25 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	end;

	if (n == 0)
	{
		dest = (char *)src;
		return (ft_strlen(src));
	}
	else
	{
		i = 0;
		while (dest[i] && i < n)
			i++;
		end = i;
		while (src[i - end] && i < n - 1)
		{
			dest[i] = src[i - end];
			i++;
		}
		if (end < n)
			dest[i] = '\0';
		return (end + ft_strlen(src));
	}
}
