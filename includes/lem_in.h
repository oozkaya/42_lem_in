/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:45:48 by oozkaya           #+#    #+#             */
/*   Updated: 2018/05/16 19:44:50 by oozkaya          ###   ########.fr       */
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
	struct s_elem	*next;
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

enum { NORMAL, START, END };

#endif
