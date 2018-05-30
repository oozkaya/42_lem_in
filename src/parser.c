/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:10:34 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/30 19:52:50 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_update_type(t_room *head, int type)
{
	t_room	*tmp;

	tmp = head;
	while (tmp->name)
	{
		if (tmp->type == type)
			tmp->type = NORMAL;
		tmp = tmp->next;
	}
}

static int	ft_parse_room(t_room **room, t_room *head, char *line)
{
	if (ft_strequ(line, "##start"))
	{
		ft_update_type(head, START);
		(*room)->type = START;
	}
	else if (ft_strequ(line, "##end"))
	{
		ft_update_type(head, END);
		(*room)->type = END;
	}
	else
		return (ft_check_room_apply(room, line));
	return (1);
}

static int	ft_parse_link(t_room *head, char *line, t_map *map, int *started)
{
	char	**links;

	if (!*started)
	{
		if (!head->name)
		{
			ft_free_map(map, head);
			ft_putstr_fd("ERROR\n", 2);
			exit(EXIT_FAILURE);
		}
		ft_check_start_end(head, map);
		ft_link_iniatilize(map, head);
		ft_update_index(head);
	}
	links = ft_strsplit(line, '-');
	if (!ft_name_is_valid(head, links) || !ft_strchr(line, '-') || links[2])
	{
		ft_free_tab(links);
		return (-1);
	}
	map->links[ft_index(head, links[0])][ft_index(head, links[1])] = LINKED;
	map->links[ft_index(head, links[1])][ft_index(head, links[0])] = LINKED;
	ft_free_tab(links);
	*started = 1;
	return (1);
}

int			ft_parser(t_map *map, t_room *head, char *line)
{
	static int	started;

	if (line[0] == '#' && line[1] == '#' && line[2] != 's' && line[2] != 'e')
		return (1);
	else if (line[0] == '#' && line[1] != '#')
		return (1);
	else if (map->ants == -1)
	{
		if (!ft_str_isdigit(line) || ft_atoi(line) < 0)
		{
			ft_free_map(map, head);
			ft_putstr_fd("ERROR\n", 2);
			exit(EXIT_FAILURE);
		}
		map->ants = ft_atoi(line);
		return (1);
	}
	else if (!ft_strchr(line, '-') && !started)
		return (ft_parse_room(&map->room, head, line));
	else if (ft_strchr(line, '-'))
		return (ft_parse_link(head, line, map, &started));
	return (-1);
}
