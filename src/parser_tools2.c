/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:17:57 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/28 15:03:45 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*ft_name(t_map *map, int index)
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

void	ft_update_type(t_room *head, int type)
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

int		ft_index_type(t_room *head, int index)
{
	t_room	*tmp;

	tmp = head;
	while (tmp->name)
	{
		if (tmp->index == index)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (-1);
}

int		ft_start_end(t_room *head)
{
	t_room	*tmp;
	int		start;
	int		end;

	start = 0;
	end = 0;
	tmp = head;
	while (tmp->name)
	{
		if (tmp->type == START)
			start = 1;
		else if (tmp->type == END)
			end = 1;
		tmp = tmp->next;
	}
	if (!start || !end)
		return (0);
	return (1);
}

void	ft_apply_link(t_map *map, t_room *head, char **links)
{
	int		index1;
	int		index2;

	index1 = ft_index(head, links[0]);
	index2 = ft_index(head, links[1]);
	map->links[index1][index2] = LINKED;
	map->links[index2][index1] = LINKED;
	map->link_qty++;
}
