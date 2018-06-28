/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 13:34:19 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/28 10:55:23 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*ft_type_name(t_map *map, int type)
{
	t_room	*room;

	room = map->room;
	while (room)
	{
		if (room->type == type)
			return (room->name);
		room = room->next;
	}
	return (NULL);
}

static void	ft_print_links(t_map *map, int fd)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map->room_qty)
	{
		j = -1;
		while (++j < map->room_qty)
		{
			if (map->links[i][j] == LINKED)
			{
				ft_putchar_fd('"', fd);
				ft_putstr_fd(ft_name(map, i), fd);
				ft_putstr_fd("\" -> \"", fd);
				ft_putstr_fd(ft_name(map, j), fd);
				ft_putstr_fd("\"\n", fd);
			}
		}
	}
}

static void	ft_print_rooms(t_map *map, int fd)
{
	int		type;
	int		i;

	i = -1;
	while (++i < map->room_qty)
	{
		type = ft_index_type(map->room, i);
		if (type != START && type != END)
		{
			ft_putchar_fd('"', fd);
			ft_putstr_fd(ft_name(map, i), fd);
			ft_putstr_fd("\";\n", fd);
		}
	}
}

void		ft_create_graph(t_map *map, int fd)
{
	ft_putendl_fd("digraph callgraph {", fd);
	ft_putendl_fd("concentrate=true", fd);
	ft_putendl_fd("edge [arrowhead=none];", fd);
	ft_putendl_fd("graph [splines=spline];", fd);
	ft_putendl_fd("node [shape = ellipse, style=filled, ", fd);
	ft_putendl_fd("color=dodgerblue2, fillcolor=dodgerblue2];", fd);
	ft_print_links(map, fd);
	ft_putchar_fd('"', fd);
	ft_putstr_fd(ft_type_name(map, START), fd);
	ft_putstr_fd("\" [fillcolor=firebrick2, color=firebrick2", fd);
	ft_putstr_fd(", shape=doubleoctagon, fontcolor=black];\n", fd);
	ft_putchar_fd('"', fd);
	ft_putstr_fd(ft_type_name(map, END), fd);
	ft_putstr_fd("\" [fillcolor=firebrick2, color=firebrick2", fd);
	ft_putstr_fd(" shape=doubleoctagon, fontcolor=black];\n", fd);
	ft_print_rooms(map, fd);
	ft_putchar_fd('}', fd);
}
