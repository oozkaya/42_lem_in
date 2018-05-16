/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:08:56 by oozkaya           #+#    #+#             */
/*   Updated: 2017/12/14 13:45:01 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_check_fd(t_list **begin, int fd)
{
	t_list	*file;

	file = *begin;
	while (file)
	{
		if (fd == (int)file->content_size)
			return (file);
		file = file->next;
	}
	file = ft_lstnew("\0", 1);
	file->content_size = fd;
	ft_lstadd(begin, file);
	return (file);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*f;
	t_list			*begin;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*tmp;

	if (fd < 0 || !line || read(fd, buf, 0) < 0 || BUFF_SIZE < 0)
		return (-1);
	begin = f;
	f = ft_check_fd(&begin, fd);
	while (!ft_memchr(f->content, '\n', ft_strlen(f->content) + 1)
			&& (ret = read(fd, buf, BUFF_SIZE)))
		MALLCHECK((f->content = ft_strnjoinfree(f->content, buf, ret, 0)));
	ret = 0;
	while (((char*)f->content)[ret] && ((char*)f->content)[ret] != '\n')
		++ret;
	MALLCHECK((*line = ft_strndup(f->content, ret)));
	(((char*)f->content)[ret] == '\n') ? ++ret : 0;
	tmp = f->content;
	MALLCHECK((f->content = ft_strdup(f->content + ret)));
	free(tmp);
	f = begin;
	return (ret ? 1 : 0);
}
