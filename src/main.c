/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:45:05 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/07 18:54:23 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	char	*line;
	t_map	map;
	t_room	*head;

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
	//while (++i < map.room_qty)
	t_room *tmp;
	tmp = head;
	while (tmp)
	{
		ft_printf("name = \"%s\"\nx = %d\ny = %d\ntype = %d\nindex = %d\n\n", tmp->name, tmp->x, tmp->y, tmp->type, tmp->index);
		tmp = tmp->next;
	}
	int i = -1;
	int j = 0;
	ft_putstr("\t");
	while (++i < map.room_qty)
		ft_printf("%d  ", i);
	ft_putstr("\n\t");
	i = 0;
	while (i++ < map.room_qty)
		ft_printf("|  ");
	ft_putstr("\n");
	i = 0;
	while (i < map.room_qty)
	{
		j = 0;
		ft_printf("[%d] --\t", i);
		while (j < map.room_qty)
		{
			ft_printf("%d  ", map.links[i][j]);
			j++;
		}
		ft_putstr("\n");
		i++;
	}
	ft_solver(&map);
//	ft_sort_paths(&map);
	ft_print_solution(&map, head);
/*	ft_printf("room_qty = %d\n", map.room_qty);
	tmp = head;
	while (tmp)
	{
		ft_printf("tmp->name = %s\n", tmp->name);
		tmp = tmp->next;
	}*/
	ft_free_map(&map, head);
//	while (1);
	return (0);
}
