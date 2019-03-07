/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_from_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:08:45 by lfatton           #+#    #+#             */
/*   Updated: 2018/06/28 15:43:52 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <limits.h>

static int	read_line(int fd, int c, char **line, char **s)
{
	size_t		len;
	char		*adrchar;

	adrchar = ft_strchr(s[fd], c);
	if (!(*line = ft_strndup(s[fd], adrchar - s[fd])))
		return (-1);
	len = ft_strlen(s[fd]) - ft_strlen(*line);
	s[fd] = ft_strsubfree(s[fd], adrchar - s[fd] + 1, len);
	return (1);
}

static int	read_end_line(int fd, char **line, char **s)
{
	if (!(*line = ft_strdup(s[fd])))
		return (-1);
	ft_strdel(&s[fd]);
	return (1);
}

int			get_next_line_from_char(const int fd, char **line, int c)
{
	static char	*s[FD_MAX];
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || fd > FD_MAX || BUFF_SIZE < 1 || !line || !ft_isascii(c))
		return (-1);
	if (!s[fd])
		s[fd] = ft_strnew(1);
	if (ft_strchr(s[fd], c))
		return (read_line(fd, c, line, s));
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		s[fd] = ft_strjoinfree(s[fd], buf, 1);
		if (ft_strchr(s[fd], c))
			return (read_line(fd, c, line, s));
	}
	if (!ft_strchr(s[fd], c) && ft_strlen(s[fd]) && !ret)
		return (read_end_line(fd, line, s));
	return (ret);
}
