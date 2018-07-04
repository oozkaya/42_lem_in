/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:39:58 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/29 11:16:03 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_ant_assign(t_map *map, t_path *path, int id)
{
	t_room	*tmp;

	tmp = map->room;
	while (tmp)
	{
		if (tmp->index == path->tab[1])
		{
			tmp->ant_id = id;
			return ;
		}
		tmp = tmp->next;
	}
}

static int	ft_ant_departure(t_map *map, int flags)
{
	int			i;
	static int	id;
	t_path		*tmp;

	i = 0;
	tmp = map->path;
	while (tmp)
	{
		id++;
		if (ft_index_type(map->room, tmp->tab[1]) == END)
		{
			while (++i <= map->ants)
			{
				if (!(flags & FLAG_Q2))
					ft_printf("L%d-%s\n", i, ft_name(map, tmp->tab[1]));
				map->laps++;
			}
			return (1);
		}
		if (id >= map->ants + 1)
			return (0);
		ft_ant_assign(map, tmp, id);
		tmp = tmp->next;
	}
	return (0);
}

static void	ft_print_all(t_map *map, int flags)
{
	t_room	*room;
	int		id;

	id = 0;
	while (id++ < map->ants)
	{
		room = map->room;
		while (room)
		{
			if (id == room->ant_id && !(flags & FLAG_Q2))
				ft_printf("L%d-%s ", id, room->name);
			room = room->next;
		}
	}
	map->laps++;
	if (!(flags & FLAG_Q2))
		ft_putchar('\n');
}

static void	ft_output(t_map *map, int flags)
{
	if (!(flags & FLAG_Q2))
		ft_putchar('\n');
	while (map->ants_arrived < map->ants)
	{
		if (ft_ant_departure(map, flags))
			return ;
		ft_print_all(map, flags);
		ft_move_all(map, flags);
	}
	map->laps++;
	if (!(flags & FLAG_Q2))
		ft_putchar('\n');
}

void		ft_print_solution(t_map *map, int flags)
{
	t_path	*tmp;

	tmp = map->path;
	if (!tmp || !map->room_qty || tmp->tab[1] == -1)
	{
		ft_putstr_fd("ERROR\n", 2);
		ft_free_map(map, map->room);
		exit(EXIT_FAILURE);
	}
	if (!(flags & FLAG_Q1))
		write(1, map->buf->str, ft_strlen(map->buf->str));
	while (tmp)
	{
		if (tmp->tab[1] == -1)
			ft_delete_path(map, &tmp);
		else
			tmp = tmp->next;
	}
	ft_output(map, flags);
}
