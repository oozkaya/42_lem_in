/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:45:48 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/22 11:11:11 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

enum { NORMAL, START, END };
enum { UNLINKED, LINKED, USED};


typedef struct	s_path
{
	int				*tab;
	int				index;
	int				size;
	int				is_valid;
	struct s_path	*next;
}				t_path;

typedef struct	s_buff
{
	char	*str;
	int		index;
	int		len;
}				t_buff;

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	int				type;
	int				index;
	int				ant_id;
	int				done;
	struct s_room	*next;
}				t_room;

typedef struct	s_ants
{
	int				id;
	t_path			*path;
	int				index;
	struct s_ants	*next;
}				t_ants;

typedef struct	s_map
{
	int		ants;
	t_room	*room;
	int		room_qty;
	int		**links;
	t_buff	*buf;
	t_path	*path;
//	t_ants	*ants_path;
	int		ants_arrived;
}				t_map;

/*
**	Buffer
*/
void			init_buffer(t_buff **buf);
void			add_buffer(t_buff **buf, char *str, size_t size);

/*
** Map init & free
*/
void			ft_map_initialize(t_map *map);
void			ft_room_initialize(t_room **room);
void			ft_link_iniatilize(t_map *map, t_room *head);
void			ft_path_initialize(t_path **path, int room_qty);

void			ft_free_map(t_map *map, t_room *head);
void			ft_free_tab(char **tab);

/*
**	Parser
*/
int				ft_parser(t_map *map, t_room *head, char *line);

int				ft_check_room_apply(t_room **room, char *line);
void			ft_check_start_end(t_room *head, t_map *map);
void			ft_update_index(t_room *head);
int				ft_name_is_valid(t_room *head, char **links);
int				ft_index(t_room *head, char *link);

void			ft_update_type(t_room *head, int type);
int				ft_index_type(t_room *head, int index);
void			ft_apply_link(t_map *map, t_room *head, char **links);

/*
** Solver
*/
char				*ft_name(t_map *map, int index);
void				ft_solver(t_map *map);

void				ft_valid_paths(t_map *map);

void				ft_delete_path(t_map *map, t_path **to_delete);

void				ft_sort_paths(t_map *map, int type);

void				ft_print_solution(t_map *map, t_room *head);

#endif
