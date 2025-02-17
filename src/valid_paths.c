/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 13:24:14 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/28 11:14:27 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ft_is_valid(int *to_check, int *tmp)
{
	int		i;
	int		j;

	i = 1;
	while (to_check[i + 1] != -1)
	{
		j = 1;
		while (tmp[j + 1] != -1)
		{
			if (to_check[i] == tmp[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void		ft_delete_path(t_map *map, t_path **to_delete)
{
	t_path	*tmp;
	t_path	*prev;
	int		del;

	del = (*to_delete)->index;
	*to_delete = (*to_delete)->next;
	tmp = map->path;
	if (tmp && tmp->index == del)
	{
		map->path = tmp->next;
		ft_memdel((void**)&tmp->tab);
		ft_memdel((void**)&tmp);
		return ;
	}
	while (tmp && tmp->index != del)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	ft_memdel((void**)&tmp->tab);
	ft_memdel((void**)&tmp);
}

void		ft_valid_paths(t_map *map)
{
	t_path	*tmp;
	t_path	*to_check;
	int		deleted;

	ft_sort_paths(map, 2);
	to_check = map->path;
	while (to_check)
	{
		tmp = map->path;
		while (tmp)
		{
			deleted = 0;
			if (to_check->index != tmp->index)
			{
				if (!ft_is_valid(to_check->tab, tmp->tab))
				{
					ft_delete_path(map, &tmp);
					deleted = 1;
				}
			}
			if (!deleted)
				tmp = tmp->next;
		}
		to_check = to_check->next;
	}
}
