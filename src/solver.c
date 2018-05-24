/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:46:15 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/24 20:03:38 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*ft_name(t_room *head, int index)
{
	t_room	*tmp;

	tmp = head;
	while (tmp->name)
	{
		if (tmp->index == index)
			return (tmp->name);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	ft_recursive(t_map *map, t_room *head, char *name, int path_index)
{
	int		i;
	t_room	*curr;
	
	curr = head;
	while (curr->name)
	{
		if (ft_strequ(curr->name, name))
			break ;
		curr = curr->next;
	}
	if (curr->type == END)
		return (1);
	i = -1;
	while (++i < map->room_qty)
	{
		if (map->links[ft_index(head, curr->name)][i])
		{
			map->path[path_index] = i;
			if (ft_recursive(map, head, ft_name(head, i), path_index + 1))
				return (1);
		}
	}
	map->path[path_index] = -1;
	return (0);
}

void	ft_solver(t_map *map, t_room *head)
{
	t_room	*tmp;

	tmp = head;
	while (tmp->name)
	{
		if (tmp->type == START)
		{
			map->path[0] = tmp->index;
			break ;
		}
		tmp = tmp->next;
	}
	ft_recursive(map, head, tmp->name, 1);
}