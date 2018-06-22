/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:46:15 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/22 19:35:20 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*ft_name(t_map *map, int index)
{
	t_room	*tmp;

	tmp = map->room;
	while (tmp->name)
	{
		if (tmp->index == index)
			return (tmp->name);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	ft_type(t_map *map, char *name)
{
	t_room	*tmp;

	tmp = map->room;
	while (tmp->name)
	{
		if (ft_strequ(tmp->name, name))
			return (tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

static void	ft_copy_path(t_path *src, t_path *dest, int room_qty)
{
	int		i;
	int		tmp;

	//while (src->tab[++i] != -1)
	i = -1;
	while (++i < room_qty)
	{
		ft_printf("|%d|-", src->tab[i]);
		tmp = src->tab[i];
		dest->tab[i] = tmp;
	}
	ft_putstr("\n");
}

static int	ft_recursive_condition(t_map *map, char *name, int path_index)
{
	if (ft_type(map, name) == END)
	{
		ft_path_initialize(&map->path->next, map->room_qty);
		//if (path_index != map->room_qty)
		ft_copy_path(map->path, map->path->next, map->room_qty);
		map->path->size = path_index + 1;
		map->path = map->path->next;
		return (1);
	}
	if (path_index == map->room_qty)
		return (1);
	return (0);
}

static void	ft_recursive(t_map *map, char *name, int path_index)
{
	int		i;
	int		j;
	int		index;

	ft_printf("path_index = %d, name = %s\n", path_index, name);
	if (ft_recursive_condition(map, name, path_index))
		return ;
	i = -1;
	index = ft_index(map->room, name);
	while (++i < map->room_qty)
	{
		ft_printf("i = %d et map->links[%d][%d] = %d\n", i , index, i , map->links[index][i]);
		if (map->links[index][i] == LINKED
			&& ft_index_type(map->room, i) != START)
		{
			map->path->tab[path_index] = i;
			//map->links[index][i] = USED;
			//if (ft_index_type(map->room, index) != START)
			//	map->links[i][index] = USED;
			j = 0;
			while (++j < map->room_qty)
			{
				if (map->links[j][index] == LINKED)
					map->links[j][index] = USED;
				//map->links[i][j] = USED;
			}
			ft_recursive(map, ft_name(map, i), path_index + 1);
			//map->links[index][i] = LINKED;
			//if (ft_index_type(map->room, index) != START)
			//	map->links[i][index] = LINKED;
			j = 0;
			while (++j < map->room_qty)
			{
				if (map->links[j][index] == USED)
					map->links[j][index] = LINKED;
				//map->links[i][j] = LINKED;
			}
		}
	}
	map->path->tab[path_index] = -1;
}

void		ft_solver(t_map *map)
{
	t_room	*tmp;
	t_path	*head;

	if (!map->room_qty)
		return ;
	head = map->path;
	tmp = map->room;
	while (tmp->name)
	{
		if (tmp->type == START)
		{
			map->path->tab[0] = tmp->index;
			break ;
		}
		tmp = tmp->next;
	}
	ft_recursive(map, tmp->name, 1);
	map->path = head;
	ft_valid_paths(map);
}
