/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:20:43 by oozkaya           #+#    #+#             */
/*   Updated: 2018/03/20 10:37:40 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# define BUFFER_SIZE 4096

# define EOC "\033[00m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define GRAY "\033[37m"

# define COLOR_LEN 5

typedef struct	s_format
{
	int		zero;
	int		minus;
	int		plus;
	int		hashtag;
	int		space;
	int		prec;
	int		prec_activated;
	int		prec_dot_activated;
	int		tmp;
	int		tmp2;
	int		tmp3;
	int		width;
	char	type_size;
	char	conv;
	char	no_conv;
}				t_format;

typedef struct	s_buffer
{
	char		*str;
	int			index;
	int			len;
	int			fd;
	int			clr_len;
	int			clr_counter;
	int			clr_check;
	int			clr_check2;
}				t_buffer;

typedef struct	s_conv
{
	char	*conversion;
	int		(*arg)(t_buffer*, t_format*, va_list);
}				t_conv;

typedef struct	s_color
{
	char	*clr;
	char	*clr_code;
}				t_color;

int				ft_color_counter(va_list ap, char *format);

char			*ft_tab_color(t_buffer *buf, char *format);
char			*color_applier1(t_buffer *buf, char *format);
char			*color_applier2(t_buffer *buf, char *format);

void			check_prec(int *check, t_format *fmt, char *arg);
void			add_prec(t_buffer *buf, t_format *fmt, char *arg, int size);
void			int_arg_sign(t_buffer *buf, t_format *fmt, char *arg);
int				int_arg_filling_size(t_format *fmt, char *arg);

int				d_arg(t_buffer *buf, t_format *fmt, va_list ap);
int				u_o_arg(t_buffer *buf, t_format *fmt, va_list ap);
int				p_x_arg(t_buffer *buf, t_format *fmt, va_list ap);
int				c_arg(t_buffer *buf, t_format *fmt, va_list ap);
int				wc_arg(t_buffer *buf, t_format *fmt, va_list ap);
int				s_arg(t_buffer *buf, t_format *fmt, va_list ap);
int				ws_arg(t_buffer *buf, t_format *fmt, va_list ap);
int				pct_arg(t_buffer *buf, t_format *fmt, va_list ap);

int				unicode_mask_applier(char *bytes, wchar_t arg);
int				ft_bytelen(wchar_t arg);

int				ft_printf(const char *format, ...);
int				ft_vprintf(const char *format, va_list ap);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_vdprintf(int fd, const char *format, va_list ap);
int				ft_asprintf(char **str, const char *format, ...);
int				ft_vasprintf(char **str, const char *format, va_list ap);
int				ft_sprintf(char *str, const char *format, ...);
int				ft_vsprintf(char *str, const char *format, va_list ap);
int				ft_snprintf(char *str, size_t size, const char *format, ...);
int				ft_vsnprintf(char *str, size_t size, const char *format,
								va_list ap);
int				ft_core_printf(t_buffer *buf, char *format, va_list ap);

char			*flags_parser(char *format, t_format *fmt);
char			*width_parser(char *format, t_format *fmt, va_list ap);
char			*precision_parser(char *format, t_format *fmt, va_list ap);
char			*type_size_parser(char *format, t_format *fmt);
int				conv_parser(char c, t_format *fmt);

void			buffer_init(t_buffer *buf);
void			buffer_add_str(t_buffer *buf, char *str, size_t size);
void			buffer_add_char(t_buffer *buf, char c, size_t size);

#endif
