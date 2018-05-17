/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:10:34 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/17 18:43:43 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_check_apply(t_room **room, char *line)
{
	char	**tab;

	tab = ft_strsplit(line, ' ');
	if (tab[3] || !ft_str_isdigit(tab[1]) || !ft_str_isdigit(tab[2]))
		return ;
	if (ft_strchr(tab[0], '-') || tab[0][0] == 'L' || tab[0][0] == '#')
		return ;
	(*room)->name = ft_strdup(tab[0]);
	(*room)->x = ft_atoi(tab[1]);
	(*room)->y = ft_atoi(tab[2]);
	ft_room_initialize(&(*room)->next);
	*room = (*room)->next;
}

static void	ft_parse_room(t_room **room, char *line)
{
	if (ft_strequ(line, "##start"))
		(*room)->type = START;
	else if (ft_strequ(line, "##end"))
		(*room)->type = END;
	else
		ft_check_apply(room, line);

}

int			ft_parser(t_map *map, char *line)
{
	if (map->ants == -1)
	{
		if (!ft_str_isdigit(line) || ft_atoi(line) < 0)
			return (-1);
		map->ants = ft_atoi(line);
	}
	else
		ft_parse_room(&map->room, line);
	return (1);
}