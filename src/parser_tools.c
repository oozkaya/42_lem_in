/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:28:46 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/30 19:00:04 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_check_room_apply(t_room **room, char *line)
{
	char	**tab;
	int		ret;

	ret = 1;
	tab = ft_strsplit(line, ' ');
	if (tab[3] || !tab[0] || !tab[1] || !tab[2])
	{
		ft_free_tab(tab);
		return (-1);
	}
	if (!ft_str_isdigit(tab[1]) || !ft_str_isdigit(tab[2]))
		ret = -1;
	if (ft_strchr(tab[0], '-') || tab[0][0] == 'L' || tab[0][0] == '#')
		ret = -1;
	if (ret == 1)
	{
		(*room)->name = ft_strdup(tab[0]);
		(*room)->x = ft_atoi(tab[1]);
		(*room)->y = ft_atoi(tab[2]);
		ft_room_initialize(&(*room)->next);
		*room = (*room)->next;
	}
	ft_free_tab(tab);
	return (ret);
}

void	ft_check_start_end(t_room *head, t_map *map)
{
	int		end;
	int		start;
	t_room	*tmp;

	end = 0;
	start = 0;
	tmp = head;
	while (tmp->name)
	{
		if (tmp->type == START)
			start = 1;
		if (tmp->type == END)
			end = 1;
		tmp = tmp->next;
	}
	if (!start || !end)
	{
		ft_free_map(map, head);
		ft_putstr_fd("ERROR\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_update_index(t_room *head)
{
	int		index;
	t_room	*tmp;

	index = 0;
	tmp = head;
	while (tmp->name)
	{
		tmp->index = index;
		tmp = tmp->next;
		index++;
	}
}

int		ft_name_is_valid(t_room *head, char **links)
{
	t_room	*tmp;
	int		found1;
	int		found2;

	if (!links[0] || !links[1] || !links)
		return (0);
	found1 = 0;
	found2 = 0;
	tmp = head;
	while (tmp->name)
	{
		if (ft_strequ(tmp->name, links[0]))
			found1 = 1;
		if (ft_strequ(tmp->name, links[1]))
			found2 = 1;
		tmp = tmp->next;
	}
	if (!found1 || !found2)
		return (0);
	return (1);
}

int		ft_index(t_room *head, char *link)
{
	t_room	*tmp;

	tmp = head;
	while (tmp->name)
	{
		if (ft_strequ(tmp->name, link))
			return (tmp->index);
		tmp = tmp->next;
	}
	return (-1);
}
