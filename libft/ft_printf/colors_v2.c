/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:35:37 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/25 20:22:20 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_color(va_list ap, char **tab, char *format)
{
	va_list aq;
	char	*arg;
	char	*color;
	int		i;
	int		counter;

	counter = 0;
	va_copy(aq, ap);
	while ((color = ft_strchr(format, '%')) != NULL)
	{
		if (color[1] == 's')
		{
			arg = va_arg(aq, char*);
			i = -1;
			while (tab[++i])
				if (ft_strequ(arg, tab[i]))
					counter++;
		}
		else
			arg = va_arg(aq, char*);
		format = color + 2;
	}
	va_end(aq);
	return (counter);
}

int			ft_color_counter(va_list ap, char *format)
{
	static char *color_tab[] = { "\033[00m",
		"\033[30m",
		"\033[31m",
		"\033[32m",
		"\033[33m",
		"\033[34m",
		"\033[35m",
		"\033[36m",
		"\033[37m",
		"\033[90m",
		"\033[91m",
		"\033[92m",
		"\033[93m",
		"\033[94m",
		"\033[95m",
		"\033[96m",
		"\033[97m",
		NULL
	};

	return (ft_count_color(ap, color_tab, format));
}
