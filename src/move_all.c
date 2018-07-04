/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 18:08:56 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/29 11:11:09 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*ft_get_room(t_map *map, int index_to_find)
{
	t_room	*room;

	room = map->room;
	while (room)
	{
		if (room->index == index_to_find)
			return (room);
		room = room->next;
	}
	return (NULL);
}

static int		ft_print_end(t_map *map, int index, t_room *room, int flags)
{
	if (ft_index_type(map->room, index) == END)
	{
		if (!(flags & FLAG_Q2))
			ft_printf("L%d-%s ", room->ant_id, ft_name(map, index));
		room->ant_id = 0;
		map->ants_arrived++;
		return (1);
	}
	return (0);
}

static t_room	*ft_get_next_room(t_map *map, t_room *room, int flags)
{
	int		i;
	t_path	*path;
	int		index_to_find;

	path = map->path;
	while (path)
	{
		i = -1;
		while (++i <= path->size)
		{
			if (path->tab[i] == room->index)
			{
				if (ft_print_end(map, path->tab[i + 1], room, flags))
					return (NULL);
				index_to_find = path->tab[i + 1];
				break ;
			}
		}
		path = path->next;
	}
	return (ft_get_room(map, index_to_find));
}

static void		ft_reset_rooms(t_map *map)
{
	t_room	*room;

	room = map->room;
	while (room)
	{
		room->done = 0;
		room = room->next;
	}
}

void			ft_move_all(t_map *map, int flags)
{
	t_room	*room;
	t_room	*next_room;
	int		id;

	id = 0;
	while (++id <= map->ants)
	{
		room = map->room;
		while (room)
		{
			if (room->ant_id == id && !room->done)
			{
				if ((next_room = ft_get_next_room(map, room, flags)))
				{
					next_room->ant_id = room->ant_id;
					next_room->done = 1;
					room->done = 1;
					room->ant_id = 0;
				}
				break ;
			}
			room = room->next;
		}
	}
	ft_reset_rooms(map);
}
