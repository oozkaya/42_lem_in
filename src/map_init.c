/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:16:11 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/16 17:55:22 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*ft_room_initialize(void)
{
	t_room	*room;

	if ((room = malloc(sizeof(*room))))
		return (NULL);
	if ((room->name = malloc(sizeof())))
}

t_map	*ft_map_initialize(void)
{
	t_map	*map;

	if (!(map = malloc(sizeof(*map))))
		return (NULL);
	
}