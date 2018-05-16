/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:22:06 by oozkaya           #+#    #+#             */
/*   Updated: 2018/02/22 21:06:05 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Initializes the buffer with a size equal to BUFFER_SIZE
** that can be modified in the "ft_printf.h" header
**
** Return : void
*/

void	buffer_init(t_buffer *buf)
{
	if (!(buf->str = malloc(sizeof(char) * BUFFER_SIZE)))
		return ;
	buf->index = 0;
	buf->len = 0;
	buf->fd = 0;
	buf->clr_len = 0;
	buf->clr_counter = 0;
	buf->clr_check = 0;
	buf->clr_check2 = 0;
}

/*
** Adds a character in the buffer as many times as the given "size"
** If BUFFER_SIZE is exceeded, we double the size of the buffer
**
** Return : void
*/

void	buffer_add_char(t_buffer *buf, char c, size_t size)
{
	size_t	new_size;

	if ((buf->index + size) >= BUFFER_SIZE)
	{
		new_size = BUFFER_SIZE;
		while ((buf->index + size) >= new_size)
			new_size *= 2;
		if (!(buf->str = ft_realloc(buf->str, new_size)))
			return ;
	}
	ft_memset(buf->str + buf->index, c, size);
	buf->index += size;
	buf->len += size;
	buf->str[buf->index] = '\0';
}

/*
** Adds a string in the buffer as big as the given "size"
** Thus a "size" smaller than the string's size will cut the string
** If BUFFER_SIZE is exceeded, we double the size of the buffer
**
** Return : void
*/

void	buffer_add_str(t_buffer *buf, char *str, size_t size)
{
	size_t	new_size;

	if ((buf->index + size) >= BUFFER_SIZE)
	{
		new_size = BUFFER_SIZE;
		while ((buf->index + size) >= new_size)
			new_size *= 2;
		if (!(buf->str = ft_realloc(buf->str, new_size)))
			return ;
	}
	ft_memmove(buf->str + buf->index, str, size);
	buf->index += size;
	buf->len += size;
	buf->str[buf->index] = '\0';
}
