/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:27:10 by oozkaya           #+#    #+#             */
/*   Updated: 2017/11/14 13:35:07 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*str2;

	len = ft_strlen(str);
	if (!(str2 = (char*)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	ft_strcpy(str2, str);
	return (str2);
}
