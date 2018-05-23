/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:10:34 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/18 16:18:08 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_update_type(t_room *head, int type)
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

static int	ft_check_apply(t_room **room, char *line)
{
	char	**tab;

//	ft_putstr("check apply entered\n");
	tab = ft_strsplit(line, ' ');
	if (tab[3] || !ft_str_isdigit(tab[1]) || !ft_str_isdigit(tab[2]))
	{
//		ft_putstr("tab error\n");
		return (-1);
	}
	if (ft_strchr(tab[0], '-') || tab[0][0] == 'L' || tab[0][0] == '#')
	{
//		ft_putstr("bad char\n");
		return (-1);
	}
	(*room)->name = ft_strdup(tab[0]);
	(*room)->x = ft_atoi(tab[1]);
	(*room)->y = ft_atoi(tab[2]);
	ft_room_initialize(&(*room)->next);
	*room = (*room)->next;
	return (1);
}

static int	ft_parse_room(t_room **room, t_room *head, char *line)
{
	if (ft_strequ(line, "##start"))
	{
//		ft_putstr("start1\n");
		ft_update_type(head, START);
		(*room)->type = START;
//		ft_putstr("start2\n");
	}
	else if (ft_strequ(line, "##end"))
	{
//		ft_putstr("end1\n");
		ft_update_type(head, END);
		(*room)->type = END;
//		ft_putstr("end2\n");
	}
	else
		return (ft_check_apply(room, line));
//	ft_putstr("OK\n");
	return (1);
}

static int	ft_name_is_valid(t_room *head, char **links)
{
	t_room	*tmp;
	int		found1;
	int		found2;

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
		return (-1);
	return (1);
}

static void	ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		ft_memdel((void**)&tab[i++]);
	ft_memdel((void**)&tab);
}

static void	ft_update_index(t_room *head)
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

static void	ft_link_iniatilize(t_map *map, t_room *head)
{
	int		i;
	int		count;
	t_room	*tmp;

	tmp = head;
	count = 0;
	while (tmp->name)
	{
		count++;
		tmp = tmp->next;
	}
	ft_printf("count = %d\n", count);
	map->links = (int**)malloc(sizeof(int*) * count);
	i = -1;
	while (++i < count)
	{
		map->links[i] = (int*)malloc(sizeof(int) * count);
		//ft_memset(map->links[i], 0, sizeof(int) * count);
		ft_bzero(map->links[i], sizeof(int) * count);//sizeof(map->links[i]));
	}
	//ft_bzero(map->links, sizeof(int*) * count);//count ^ 2);
	ft_putstr("ok\n");
	map->links[0][3] = 9;
}

static int	ft_parse_link(t_room *head, char *line, t_map *map, int *started)
{
	t_room	*tmp;
	char	**links;

	if (!*started)
	{
		ft_link_iniatilize(map, head);
		ft_update_index(head);
		map->links[0][1] = 5;
		ft_printf("links = %d\n", map->links[0][2]);
	}
	links = ft_strsplit(line, '-');
	if (ft_name_is_valid(head, links) == -1 || !ft_strchr(line, '-'))
	{
//		ft_putstr("error name\n");
		ft_free_tab(links);
		return (-1);
	}
	tmp = head;
	while (tmp->name)
	{
		if (ft_strequ(tmp->name, links[0]))
			ft_putstr("done\n");
		tmp = tmp->next;
	}
	*started = 1;
	return (1);
}

int			ft_parser(t_map *map, t_room *head, char *line)
{
	static int	started;

	if (map->ants == -1)
	{
		if (!ft_str_isdigit(line) || ft_atoi(line) < 0)
			exit(EXIT_FAILURE);
		map->ants = ft_atoi(line);
		return (1);
//		ft_putstr("ant done\n");
	}
	if (line[0] == '#' && line[1] != '#')
	{
//		ft_putstr("OK4\n");
		return (1);
	}
	else if (!ft_strchr(line, '-') && !started)
	{
//		ft_putstr("start parse room\n");
		return (ft_parse_room(&map->room, head, line));
	}
	else
	{
//		ft_putstr("end parse link\n");
		return (ft_parse_link(head, line, map, &started));
	}
	return (1);
}
