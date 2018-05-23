/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:45:05 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/18 16:14:30 by oozkaya          ###   ########.fr       */
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
//	ft_putstr("OK1\n");
	while (get_next_line(0, &line) > 0)
	{
//		ft_putstr("OK2\n");
		if (ft_parser(&map, head, line) == -1)
		{
			ft_putstr("Error ft_parser\n");
			break ;
		}
		ft_putendl(line);
		ft_memdel((void**)&line);
	}
	ft_memdel((void**)&line);
	ft_printf("ants = %d\n", map.ants);
	while (head)
	{
		ft_printf("name = \"%s\"\nx = %d\ny = %d\ntype = %dindex = %d\n\n", head->name, head->x, head->y, head->type, head->index);
		head = head->next;
	}
	return (0);
}
