/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:45:18 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/28 11:14:59 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_insert_to_revsorted(t_path **sorted, t_path *to_insert)
{
	t_path *curr;

	if (!*sorted || (*sorted)->size >= to_insert->size)
	{
		to_insert->next = *sorted;
		*sorted = to_insert;
	}
	else
	{
		curr = *sorted;
		while (curr->next && curr->next->size < to_insert->size)
			curr = curr->next;
		to_insert->next = curr->next;
		curr->next = to_insert;
	}
}

static void	ft_insert_to_sorted(t_path **sorted, t_path *to_insert)
{
	t_path *curr;

	if (!*sorted || (*sorted)->size <= to_insert->size)
	{
		to_insert->next = *sorted;
		*sorted = to_insert;
	}
	else
	{
		curr = *sorted;
		while (curr->next && curr->next->size > to_insert->size)
			curr = curr->next;
		to_insert->next = curr->next;
		curr->next = to_insert;
	}
}

static void	ft_clear_index(t_map *map)
{
	int		i;
	t_path	*path;

	path = map->path;
	while (path)
	{
		if (path->tab[1] == -1)
			ft_delete_path(map, &path);
		else
			path = path->next;
	}
	i = -1;
	path = map->path;
	while (path)
	{
		path->index = ++i;
		path = path->next;
	}
}

void		ft_sort_paths(t_map *map, int type)
{
	t_path	*sorted;
	t_path	*curr;
	t_path	*next;

	sorted = NULL;
	curr = map->path;
	while (curr)
	{
		next = curr->next;
		if (type == 1)
			ft_insert_to_sorted(&sorted, curr);
		else if (type == 2)
			ft_insert_to_revsorted(&sorted, curr);
		curr = next;
	}
	map->path = sorted;
	ft_clear_index(map);
}
