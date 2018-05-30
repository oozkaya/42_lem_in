/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:39:58 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/30 18:37:26 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_print_solution(t_map *map, t_room *head)
{
	t_path	*tmp;

	tmp = map->path;
	if (!map->room_qty || tmp->tab[1] == -1)
	{
		ft_putstr_fd("Invalid map\n", 2);
		ft_free_map(map, head);
		exit(EXIT_FAILURE);
	}
	write(1, map->buf->str, ft_strlen(map->buf->str));
	int	j = -1;
	while (tmp)
	{
		int i = -1;
		ft_printf("tab num %d : ", ++j);
		while (tmp->tab[++i] != -1 && i < map->room_qty)
			ft_printf("[%d]-", tmp->tab[i]);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}