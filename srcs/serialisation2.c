/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialisation2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:37:45 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 03:37:47 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "doom.h"
#include "serialisation.h"

void	read_str_from_file(int fd, char **name)
{
	char *c;
	char *new_name;

	c = ft_strnew(1);
	*name = ft_strnew(1);
	while (1)
	{
		if (read(fd, c, sizeof(char)) <= 0)
			error_doom("couldn't read str in file");
		new_name = ft_strjoin(*name, c);
		free(*name);
		*name = new_name;
		if (!*c)
		{
			free(c);
			return ;
		}
	}
}

void	write_str_to_file(int fd, char *name)
{
	char	*c;
	int		i;

	if (!name)
		error_doom("can't write null str");
	i = 0;
	while (1)
	{
		c = name + i++;
		write(fd, c, sizeof(char));
		if (!*c)
			return ;
	}
}

void	copy_file_in_file2(int fd, int name_fd, char **buffer)
{
	int	read_bytes;

	while (1)
	{
		read_bytes = read(name_fd, *buffer, 1024);
		if (read_bytes < 0)
			error_doom("error while copying from file");
		if (write(fd, *buffer, read_bytes) != read_bytes)
			error_doom("error while copying to file");
		if (read_bytes < 1024)
			break ;
	}
}

void	copy_file_in_file(int fd, char *name)
{
	int			name_fd;
	char		*buffer;
	struct stat	statbuf;
	int			size;

	if ((name_fd = open(name, O_RDONLY)) < 0)
		error_doom("couldn't open other file");
	if (fstat(name_fd, &statbuf) < 0)
		error_doom("couldn't find file stats");
	size = statbuf.st_size;
	if (write(fd, &size, sizeof(size)) <= 0)
		error_doom("couldn't write file size");
	if (!(buffer = malloc(1024)))
		error_doom("couln't allocate buffer");
	copy_file_in_file2(fd, name_fd, &buffer);
	free(buffer);
	close(name_fd);
}

void	create_tmp_file_from_file(int fd, char *name)
{
	int		tmp_fd;
	int		read_bytes;
	int		bytes_to_read;
	char	*buffer;

	tmp_fd = open(name, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (tmp_fd <= 0)
		error_doom("mabite couldn't open file");
	if (read(fd, &bytes_to_read, sizeof(bytes_to_read)) <= 0)
		error_doom("couldn't read bytes_to_read");
	if (!(buffer = malloc(bytes_to_read)))
		error_doom("couldn't malloc buffer");
	read_bytes = read(fd, buffer, bytes_to_read);
	if (read_bytes <= 0)
		error_doom("rip");
	if (write(tmp_fd, buffer, read_bytes) != bytes_to_read)
		error_doom("oh no");
	free(buffer);
	close(tmp_fd);
}
