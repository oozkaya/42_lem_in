/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:45:05 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/24 19:22:41 by oozkaya          ###   ########.fr       */
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
	ft_solver(&map, head);
	write(1, map.buf->str, ft_strlen(map.buf->str));
	//while (++i < map.room_qty)	
	int i = -1;
	while (map.path[++i] != -1)
		ft_printf("[%d]-", map.path[i]);
	ft_putstr("\n");
/*	while (head)
	{
		ft_printf("name = \"%s\"\nx = %d\ny = %d\ntype = %d\nindex = %d\n\n", head->name, head->x, head->y, head->type, head->index);
		head = head->next;
	}
	int i = 0;
	int j = 0;
	ft_putstr("\t0  1  2  3  4  5  6  7\n");
	ft_putstr("\t|  |  |  |  |  |  |  |\n");
	while (i < 8)
	{
		j = 0;
		ft_printf("[%d] --\t", i);
		while (j < 8)
		{
			ft_printf("%d  ", map.links[i][j]);
			j++;
		}
		ft_putstr("\n");
		i++;
	}*/
	return (0);
}
