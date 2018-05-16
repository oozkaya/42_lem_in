/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capitalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 10:21:37 by oozkaya           #+#    #+#             */
/*   Updated: 2017/11/23 10:24:34 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_capitalize(char *str)
{
	int		i;

	if (!str)
		return (NULL);
	ft_strlwr(str);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i - 1]) && ft_isalnum(str[i]))
			str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}
