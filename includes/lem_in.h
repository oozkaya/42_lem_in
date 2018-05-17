/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:45:48 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/17 18:34:44 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	int				type;
	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	char			*room1;
	char			*room2;
	struct s_link	*next;
}				t_link;

typedef struct	s_map
{
	int		ants;
	t_room	*room;
	t_link	*link;
}				t_map;


int				ft_parser(t_map *map, char *line);
void			ft_map_initialize(t_map *map);
void			ft_room_initialize(t_room **room);

enum { NORMAL, START, END };

#endif
