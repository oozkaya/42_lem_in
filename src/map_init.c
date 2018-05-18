/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:16:11 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/18 16:09:42 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_room_initialize(t_room **room)
{
	if (!(*room = malloc(sizeof(t_room))))
		return ;
	(*room)->name = NULL;
	(*room)->x = 0;
	(*room)->y = 0;
	(*room)->type = NORMAL;
	//(*room)->link = NULL;
	(*room)->index = 0;
	(*room)->prev = NULL;
	(*room)->next = NULL;
}

void	ft_map_initialize(t_map *map)
{
//	t_map	*map;

//	if (!(map = malloc(sizeof(t_map))))
//		return (NULL);
	map->ants = -1;
	ft_room_initialize(&map->room);
	//ft_room_initialize(&map->room);
	//ft_printf("inside map %d\n", map->room->x);
//	if ((map->link = malloc(sizeof(*link))))
//		return (NULL);
//	map->link->room1 = NULL;
//	map->link->room2 = NULL;*/
//	return (map);
}