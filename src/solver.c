/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:46:15 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/30 18:31:23 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*ft_name(t_map *map, int index)
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
	t_room *tmp;

	tmp = map->room;
	while (tmp->name)
	{
		if (ft_strequ(tmp->name, name))
			return (tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

/*static int	ft_recursive2(t_map *map, t_room *head, char *name, int path_index, t_path *path)
{
	int		i;

	if (ft_type(head, name) == END)
		return (1);
	if (path_index == map->room_qty)
		return (0);
	i = -1;
	while (++i < map->room_qty)
	{
		if (map->links[ft_index(head, name)][i] == 1)
		{
			path->tab[path_index] = i;
			map->links[ft_index(head, name)][i] = 2;
			if (ft_recursive2(map, head, ft_name(head, i), path_index + 1, path))
				return (1);
			map->links[ft_index(head, name)][i] = 1;
		}
	}
	path->tab[path_index] = -1;
	return (0);
}*/

static void	ft_copy_path(t_path *src, t_path *dest)
{
	int		i;
	int		tmp;

	i = -1;
	while (src->tab[++i] != -1)
	{
		tmp = src->tab[i];
		dest->tab[i] = tmp;
	}
}

static int	ft_recursive_condition(t_map *map, char *name, int path_index)
{
	if (ft_type(map, name) == END)
	{
		ft_path_initialize(&map->path->next, map->room_qty);
		if (path_index != map->room_qty)
			ft_copy_path(map->path, map->path->next);
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
	int		index;

	if (ft_recursive_condition(map, name, path_index))
		return ;
	i = -1;
	index = ft_index(map->room, name);
	while (++i < map->room_qty)
	{
		if (map->links[index][i] == LINKED)
		{
			map->path->tab[path_index] = i;
			map->links[index][i] = USED;
			map->links[i][index] = USED;
			ft_recursive(map, ft_name(map, i), path_index + 1);
			map->links[index][i] = LINKED;
			map->links[i][index] = LINKED;
		}
	}
	map->path->tab[path_index] = -1;
}

void	ft_solver(t_map *map)
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
/*	while (ft_recursive(map, head, tmp->name, 1, curr))
	{
		ft_path_initialize(&curr->next, map->room_qty);
		curr = curr->next;
		curr->tab[0] = map->path->tab[0];
	}*/
	ft_recursive(map, tmp->name, 1);
	map->path = head;
}