/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:10:34 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/16 19:53:26 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_parse_room(t_map **map, char *line)
{
	t_room	*tmp;

	tmp = (*map)->room;
	if (ft_strequ(line, "##start"))
		tmp->type = START;
	
}

int		ft_parser(t_map **map, char *line)
{
	if ((*map)->ants == -1)
	{
		if (!ft_str_isdigit(line) || ft_atoi(line) < 0)
			return (-1);
		(*map)->ants = ft_atoi(line);
	}
	ft_parse_room(map, line);
	return (1);
}