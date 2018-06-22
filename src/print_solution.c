/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:39:58 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/22 19:41:07 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*static int	ft_count_paths(t_map *map)
{
	t_path	*tmp;
	int		count;

	count = 0;
	tmp = map->path;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	ft_assign_path(t_map *map)
{
	int		id;
	int		i;
	int		total_paths;
	t_ants	*tmp;
	t_path	*tmp2;

	if (!(map->ants_path = (t_ants*)malloc(sizeof(t_ants))))
		return ;
	total_paths = ft_count_paths(map);
	id = 0;
	tmp = map->ants_path;
	tmp2 = map->path;
	i = 0;
	ft_printf("nbr ants = %d et total_paths = %d\n", map->ants, total_paths);
	while (++id <= map->ants)
	{
		ft_printf("id = %d\n", id);
		if (i == total_paths)
		{
			i = 0;
			tmp2 = map->path;
		}
		ft_putstr("OK\n");
		//if (id != map->ants)
		if (id != map->ants && !(tmp->next = (t_ants*)malloc(sizeof(t_ants))))
			return ;
		tmp->id = id;
		tmp->path = tmp2;
		tmp->index = 1;
		i++;
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	//tmp->next = NULL;
}

static int ft_type(t_map *map, t_ants *curr_ant)
{
	t_room	*tmp;

	tmp = map->room;
	while (tmp->name)
	{
		if (curr_ant->path->tab[tmp->index] == tmp->index)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

static void	ft_output(t_map *map)
{
	int		i;
	int		ants_arrived;
	int		total_paths;
	t_ants	*tmp;

	total_paths = ft_count_paths(map);
	ants_arrived = 0;
	while (ants_arrived != map->ants)
	{
		tmp = map->ants_path;
		i = 0;
		while (++i <= total_paths)
		{
			//ft_printf("L%d-", tmp->id);
			//ft_printf("%s ", ft_name(map, tmp->path->tab[tmp->index]));
			sleep(1);
			ft_printf("L%d-%s ", tmp->id, ft_name(map, tmp->path->tab[tmp->index]));
			tmp->index++;
			tmp = tmp->next;
			if (ft_type(map, tmp) == END)
				ants_arrived++;
		}
		ft_putstr("\n");
	}
}*/

/*static void	ft_move_to_next(t_map *map, t_path *path, int index, int id)
{
	t_room	*tmp;

	tmp = map->room;
	while (tmp)
	{
		if (tmp->index == path->tab[index])
			tmp->ant_id = 0;
		if (tmp->index == path->tab[index + 1])
			tmp->ant_id = id;
		tmp = tmp->next;
	}
}*/

/*static void	ft_prev_departure(t_map *map)
{
	t_path	*path;
	t_room	*room;

	path = map->path;
	while (path)
	{
		room = map->room;
		while (room)
		{
			if (room->index == path->tab[1] && room->ant_id)
				ft_move_to_next(map, path, 1, room->ant_id);
			room = room->next;
		}
		path = path->next;
	}
}*/

static void	ft_ant_assign(t_map *map, t_path *path, int id)
{
	t_room	*tmp;

	tmp = map->room;
	while (tmp)
	{
		if (tmp->index == path->tab[1])
		{
		//ft_printf("tmp->index = %d et path->tab[1] = %d\n", tmp->index, path->tab[1]);
			tmp->ant_id = id;
			return ; 
		}
		tmp = tmp->next;
	}
}

static void	ft_ant_departure(t_map *map)
{
	static int	id;
	t_path		*tmp;

//	ft_prev_departure(map);
	tmp = map->path;
	while (tmp)
	{
		id++;
		if (id >= map->ants + 1)
			return ;
		//ft_printf("id = %d\n", id);
		ft_ant_assign(map, tmp, id);
		tmp = tmp->next;
	}
}

static int ft_type(t_map *map, int index)
{
	t_room	*tmp;

	tmp = map->room;
	while (tmp->name)
	{
		if (index == tmp->index)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

static t_room	*ft_get_next_room(t_map *map, int id)
{
	t_room	*room;
	t_path	*path;
	int		index_to_find;
	int		i;
	//int		done;

	room = map->room;
	while (room)
	{
		if (room->ant_id == id)
		{
			////ft_printf("first id = %d\n", id);
			break ;
		}
		room = room->next;
	}
	path = map->path;
	//done = 0;
	while (path) //&& !done)
	{
		i = -1;
		while (++i <= path->size)
		{
			if (path->tab[i] == room->index)
			{
				//if (!path->tab[i + 1] || path->tab[i + 1] == -1)
				////ft_printf("id = %d et index = %d et path->tab[i] = %d et path->tab[i + 1] = %d\n", id, room->index, path->tab[i], path->tab[i + 1]);
				if (ft_type(map, path->tab[i + 1]) == END)
				{
					///ft_printf("done for id = %d\n", id);
					ft_printf("L%d-%s ", id, ft_name(map, path->tab[i + 1]));
					room->ant_id = 0;
					map->ants_arrived++;
					return (NULL);
				}
				index_to_find = path->tab[i + 1];
				//done = 1;
				break ;
			}
		}
		path = path->next;
	}
	////ft_printf("next_room->index = %d\n", index_to_find);
	room = map->room;
	while (room)
	{
		if (room->index == index_to_find)
			return (room);
		room = room->next;
	}
	return (NULL);
}

static void	ft_move_all(t_map *map)
{
	t_room	*room;
	t_room	*next_room;
	int		id;

	///ft_printf("ACCESS TO FT_MVOE_ALL\n");
	id = 0;
	while (++id <= map->ants)
	{
	room = map->room;
	while (room)
	{
		if (room->ant_id == id)
		{
		//if (room->ant_id && room->ant_id != map->ants + 1
		////ft_printf("room->id = %d et room->done = %d\n", room->ant_id, room->done);
		////ft_printf("room->index = %d\n", room->index);
		if (room->ant_id && !room->done
				&& (next_room = ft_get_next_room(map, room->ant_id)))
		{
			///ft_printf("room->index = %d\n", room->index);
			next_room->ant_id = room->ant_id;
			//ft_printf("next_room->ant_id = %d et room->ant_id = %d\n", next_room->ant_id, room->ant_id);
			//ft_printf("next_room->index = %d et room->index = %d\n", next_room->index, room->index);
			next_room->done = 1;
			room->done = 1;
			room->ant_id = 0;
		}
		break ;
		}
		room = room->next;
	}
	}
	room = map->room;
	while (room)
	{
		room->done = 0;
		room = room->next;
	}
}

static void	ft_print_all(t_map *map)
{
	t_room	*room;
	int		id;

	id = 0;
	while (id++ < map->ants)
	{
		room = map->room;
		while (room)
		{
			if (id == room->ant_id)
				ft_printf("L%d-%s ", id, room->name);
			room = room->next;
		}
	}
	ft_putchar('\n');
}

static void	ft_output(t_map	*map)
{
	while (map->ants_arrived < map->ants)
	{
		//ft_printf("ants_arrived = %d\n", map->ants_arrived);
		ft_ant_departure(map);
/*	t_room *tmp = map->room;
	while (tmp)
	{
		ft_printf("name = \"%s\"\nx = %d\ny = %d\ntype = %d\nindex = %d\ntmp->ant_id = %d\n\n", tmp->name, tmp->x, tmp->y, tmp->type, tmp->index, tmp->ant_id);
		tmp = tmp->next;
	}*/
		ft_print_all(map);
		ft_move_all(map);
/*	t_room *tmp;
	tmp = map->room;
	while (tmp)
	{
		ft_printf("name = \"%s\"\nant_id = %d\nindex = %d\n\n", tmp->name, tmp->ant_id, tmp->index);
		tmp = tmp->next;
	}*/
	}
	ft_putchar('\n');
}

void	ft_print_solution(t_map *map, t_room *head)
{
//	t_ants	*tmpants;
	t_path	*tmp;

	tmp = map->path;
	if (!map->room_qty || tmp->tab[1] == -1)
	{
		ft_printf("map->room_qty = %d et tmp->tab[1] = %d\n", map->room_qty, tmp->tab[1]);
		ft_putstr_fd("Invalid map\n", 2);
		ft_free_map(map, head);
		exit(EXIT_FAILURE);
	}
//	write(1, map->buf->str, ft_strlen(map->buf->str));
//	int	j = -1;
	while (tmp)
	{
		if (tmp->tab[1] == -1)
			ft_delete_path(map, &tmp);
		else
			tmp = tmp->next;
	}
	ft_sort_paths(map, 2);
	tmp = map->path;
	while (tmp)
	{
		int i = -1;
//		ft_printf("tab num %d : ", ++j);
		ft_printf("tab num %d : ", tmp->index);
		while (tmp->tab[++i] != -1 && i < map->room_qty)
			ft_printf("[%d]-", tmp->tab[i]);
		ft_putstr("\n");
		tmp = tmp->next;
	}
	ft_output(map);
	/*ft_assign_path(map);
	tmpants = map->ants_path;
	while (tmpants)
	{
		ft_printf("tab num %d for id num %d\n", tmpants->path->index, tmpants->id);
		tmpants = tmpants->next;
	}
	ft_output(map);*/

}