/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:16:11 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/24 19:01:29 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_map_initialize(t_map *map)
{
	map->ants = -1;
	ft_room_initialize(&map->room);
	map->room_qty = 0;
	map->links = NULL;
	init_buffer(&map->buf);
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
	(*room)->next = NULL;
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
	if (!(map->path = (int*)malloc(sizeof(int) * map->room_qty)))
		return ;
	ft_memset(map->path, -1, sizeof(int) * map->room_qty);
}

void	ft_free_map(t_map *map)
{
	int		i;

	ft_memdel((void**)&map->room);
	if (map->links)
	{
		i = -1;
		while (++i < map->room_qty)
			ft_memdel((void**)&map->links[i]);
		ft_memdel((void**)&map->links);
	}
	ft_memdel((void**)&map->buf->str);
	ft_memdel((void**)&map->buf);
	ft_memdel((void**)&map->path);
}

void	ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		ft_memdel((void**)&tab[i++]);
	ft_memdel((void**)&tab);
}
