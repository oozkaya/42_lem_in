/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:16:11 by oozkaya           #+#    #+#             */
/*   Updated: 2018/07/04 10:40:37 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_map_initialize(t_map *map)
{
	map->ants = -1;
	ft_room_initialize(&map->room);
	map->room_qty = 0;
	map->link_qty = 0;
	map->links = NULL;
	init_buffer(&map->buf);
	map->ants_arrived = 0;
	map->laps = 0;
}

void	ft_room_initialize(t_room **room)
{
	if (!(*room = (t_room*)malloc(sizeof(t_room))))
		return ;
	(*room)->name = NULL;
	(*room)->x = 0;
	(*room)->y = 0;
	(*room)->type = NORMAL;
	(*room)->index = 0;
	(*room)->ant_id = 0;
	(*room)->done = 0;
	(*room)->next = NULL;
}

void	ft_path_initialize(t_path **path, int room_qty)
{
	if (!(*path = (t_path*)malloc(sizeof(t_path))))
		return ;
	if (!((*path)->tab = (int*)malloc(sizeof(int) * room_qty)))
		return ;
	ft_memset((*path)->tab, -1, sizeof(int) * room_qty);
	(*path)->index = 0;
	(*path)->size = 0;
	(*path)->next = NULL;
}

void	ft_link_iniatilize(t_map *map, t_room *head)
{
	int		i;
	t_room	*tmp;

	tmp = head;
	while (tmp->name)
	{
		map->room_qty++;
		tmp = tmp->next;
	}
	if (!(map->links = (int**)malloc(sizeof(int*) * map->room_qty)))
		return ;
	i = -1;
	while (++i < map->room_qty)
	{
		if (!(map->links[i] = (int*)malloc(sizeof(int) * map->room_qty)))
			return ;
		ft_bzero(map->links[i], sizeof(int) * map->room_qty);
	}
	ft_path_initialize(&map->path, map->room_qty);
}
