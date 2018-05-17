/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:45:05 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/17 18:44:29 by oozkaya          ###   ########.fr       */
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
		if (ft_parser(&map, line) == -1)
		{
			ft_putstr("Error ft_parser\n");
			return (-1);
		}
	}
	ft_printf("ants = %d\n", map.ants);
	while (head)
	{
		ft_printf("name = \"%s\"\nx = %d\ny = %d\ntype = %d\n\n", head->name, head->x, head->y, head->type);
		head = head->next;
	}
	return (0);
}