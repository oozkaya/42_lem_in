/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 19:48:37 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/28 11:08:27 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_main_info(t_map *map)
{
	ft_printf("%s<======> Main Info <=======>%s\n\n", LRED, EOC);
	ft_printf("\t%sAnts =%s %d\n", LCYAN, EOC, map->ants);
	ft_printf("\t%sRooms =%s %d\n", LCYAN, EOC, map->room_qty);
	ft_printf("\t%sLinks =%s %d\n\n", LCYAN, EOC, map->link_qty);
}

static void	ft_room_index(t_map *map)
{
	int		i;
	t_room	*room;

	ft_printf("%s<======> Room Index <=======>%s\n\n", LRED, EOC);
	i = -1;
	while (++i < map->room_qty)
	{
		room = map->room;
		while (room)
		{
			if (room->index == i)
			{
				ft_printf("\t%s%d%s | \"%s\"\n", LCYAN, i, EOC, room->name);
				break ;
			}
			room = room->next;
		}
	}
	ft_printf("\n");
}

static void	ft_links_info(t_map *map)
{
	int i;
	int j;

	i = -1;
	while (++i < map->room_qty)
		ft_printf("%d  ", i);
	ft_putstr("\n      ");
	i = -1;
	while (++i < map->room_qty)
		ft_printf("_  ");
	ft_putchar('\n');
	i = -1;
	while (++i < map->room_qty)
	{
		j = -1;
		ft_printf(" %d  | ", i);
		while (++j < map->room_qty)
		{
			if (map->links[i][j] == 1)
				ft_printf("%s%d%s  ", LGREEN, map->links[i][j], EOC);
			else
				ft_printf("%s%d%s  ", GRAY, map->links[i][j], EOC);
		}
		ft_putchar('\n');
	}
}

void		ft_paths_info(t_map *map, int choice)
{
	int		i;
	t_path	*path;

	ft_sort_paths(map, 2);
	if (choice == 1)
		ft_printf("\n%s<======> All Paths <=======>%s\n\n", LRED, EOC);
	else
		ft_printf("%s<======> Valid Paths <=====>%s\n\n", LRED, EOC);
	path = map->path;
	while (path)
	{
		i = -1;
		while (++i < map->room_qty && ft_name(map, path->tab[i]) != NULL)
		{
			if (ft_index_type(map->room, path->tab[i]) == END)
				ft_printf("%s%s%s\n", LCYAN, ft_name(map, path->tab[i]), EOC);
			else
				ft_printf("%s%s%s %s->%s ", LCYAN, ft_name(map, path->tab[i]),
							EOC, GRAY, EOC);
		}
		path = path->next;
	}
	ft_putchar('\n');
	if (choice != 1)
		ft_printf("%s<==========================>%s\n\n", LRED, EOC);
}

void		ft_map_info(t_map *map)
{
	ft_main_info(map);
	ft_room_index(map);
	ft_printf("%s<======> Links Info <=======>%s\n\n      ", LRED, EOC);
	ft_links_info(map);
}
