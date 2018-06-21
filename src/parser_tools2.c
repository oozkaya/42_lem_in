/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:17:57 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/07 17:51:39 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	ft_apply_link(t_map *map, t_room *head, char **links)
{
	int		index1;
	int		index2;

	index1 = ft_index(head, links[0]);
	index2 = ft_index(head, links[1]);
	map->links[index1][index2] = LINKED;
	map->links[index2][index1] = LINKED;
}