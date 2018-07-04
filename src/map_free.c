/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:48:06 by oozkaya           #+#    #+#             */
/*   Updated: 2018/07/04 08:48:20 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_free_map(t_map *map, t_room *head)
{
	int		i;
	t_room	*curr;
	t_path	*cur;

	while ((curr = head) != NULL)
	{
		head = head->next;
		ft_memdel((void**)&curr->name);
		ft_memdel((void**)&curr);
	}
	if (map->links)
	{
		i = -1;
		while (++i < map->room_qty)
			ft_memdel((void**)&map->links[i]);
		ft_memdel((void**)&map->links);
	}
	ft_memdel((void**)&map->buf->str);
	ft_memdel((void**)&map->buf);
	while ((cur = map->path) != NULL)
	{
		map->path = map->path->next;
		ft_memdel((void**)&cur->tab);
		ft_memdel((void**)&cur);
	}
}

void	ft_free_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		ft_memdel((void**)&tab[i]);
	ft_memdel((void**)&tab);
}
