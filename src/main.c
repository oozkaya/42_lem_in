/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:45:05 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/28 20:22:53 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_detailed_room_info(t_map *map)
{
	t_room	*tmp;
	int		type;
	char	*color;

	tmp = map->room;
	while (tmp->name)
	{
		type = ft_index_type(map->room, tmp->index);
		if (type == START || type == END)
			color = LRED;
		else
			color = LCYAN;
		ft_printf("%sname =%s \"%s\"\n%sx =%s %d\n%sy =%s %d\n"
					"%stype =%s %d\n%sindex =%s %d\n\n",
					color, EOC, tmp->name, color, EOC, tmp->x,
					color, EOC, tmp->y, color, EOC, tmp->type,
					color, EOC, tmp->index);
		tmp = tmp->next;
	}
	ft_printf("%s<==========================>%s\n\n", LRED, EOC);
}

static void	ft_solve_print(t_map *map, int flags)
{
	if (flags & FLAG_I)
		ft_map_info(map);
	ft_solver(map, flags);
	if (flags & FLAG_I)
		ft_paths_info(map, 2);
	if (flags & FLAG_R)
		ft_detailed_room_info(map);
	ft_print_solution(map);
	if (flags & FLAG_L)
		ft_printf("\n%sTotals laps =%s %d\n", LCYAN, EOC, map->laps);
	if (flags & FLAG_G)
		ft_graph(map);
}

int			main(int ac, char **av)
{
	char	*line;
	int		flags;
	t_map	map;
	t_room	*head;

	flags = NO_FLAG;
	ft_flag_checker(ac, av, &flags);
	ft_map_initialize(&map);
	head = map.room;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_parser(&map, head, line) == -1)
			break ;
		add_buffer(&map.buf, line, ft_strlen(line));
		add_buffer(&map.buf, "\n", 1);
		ft_memdel((void**)&line);
	}
	ft_memdel((void**)&line);
	map.room = head;
	ft_solve_print(&map, flags);
	ft_free_map(&map, head);
	return (0);
}
