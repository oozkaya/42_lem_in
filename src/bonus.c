/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 12:06:23 by oozkaya           #+#    #+#             */
/*   Updated: 2018/06/28 16:16:40 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_usage(void)
{
	ft_putstr("Usage: ./lem-in [options] > [map]\n");
	ft_putstr("Options : -i to display map informations\n");
	ft_putstr("\t  -r to display detailed rooms informations\n");
	ft_putstr("\t  -g to create a graph in PNG format\n");
}

static void	ft_flag_parse(char *str, int *flags)
{
	int		i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 'i')
			*flags |= FLAG_I;
		else if (str[i] == 'l')
			*flags |= FLAG_L;
		else if (str[i] == 'r')
			*flags |= FLAG_R;
		else if (str[i] == 'g')
			*flags |= FLAG_G;
		else
		{
			ft_usage();
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void		ft_flag_checker(int ac, char **av, int *flags)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' && !ft_isdigit(av[i][1]))
		{
			ft_flag_parse(av[i], flags);
			i++;
		}
		else
			return ;
	}
}

void		ft_graph(t_map *map)
{
	int		fd;

	fd = open("graph.dot", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (fd == -1)
	{
		ft_putstr_fd("Error open()\n", 2);
		ft_free_map(map, map->room);
		exit(EXIT_FAILURE);
	}
	ft_create_graph(map, fd);
	system("dot -Tpng graph.dot -o graph.png");
	system("rm graph.dot");
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error close()\n", 2);
		ft_free_map(map, map->room);
		exit(EXIT_FAILURE);
	}
}
