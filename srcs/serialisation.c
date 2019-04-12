#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "libft.h"
#include "doom.h"
#include "serialisation.h"

void	read_file(char *filename, t_textures **textures, t_map **map)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd <= 0)
        error_doom("couldn't open file");
    read_textures_from_file(fd, textures);
    read_map_from_file(fd, *textures, map);
    close(fd);
}

void	write_file(char *filename, t_textures *textures, t_map *map)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd <= 0)
        error_doom("couldn't open file");
    write_textures_to_file(fd, textures);
    write_map_to_file(fd, map);
    close(fd);
}

void	read_str_from_file(int fd, char **name)
{
    char			*c;
    char			*new_name;

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
            return;
        }
    }
}

void	write_str_to_file(int fd, char *name)
{
    char			*c;
    int				i;

    if (!name)
        error_doom("can't write null str");
    i = 0;
    while (1)
    {
        c = name + i++;
        write(fd, c, sizeof(char));
        if (!*c)
            return;
    }
}

void	copy_file_in_file(int fd, char *name)
{
    int				read_bytes;
    int 			name_fd;
    char			*buffer;
    struct stat		statbuf;

    if ((name_fd = open(name, O_RDONLY)) < 0)
        error_doom("couldn't open file");
    if (fstat(fd, &statbuf) < 0)
        error_doom("couldn't find file stats");
    if (write(fd, &statbuf.st_size, sizeof(statbuf.st_size)) <= 0)
        error_doom("couldn't write file size");
    if (!(buffer = malloc(1024)))
        error_doom("couln't allocate buffer");
    while (1)
    {
        read_bytes = read(name_fd, buffer, 1024);
        if (read_bytes < 0)
            error_doom("error while copying from file");
        if (write(fd, buffer, 1024) != read_bytes)
            error_doom("error while copying to file");
        if (read_bytes < 1024)
            break;
    }
    free(buffer);
    close(name_fd);
}

void	create_tmp_file_from_file(int fd, char *name)
{
    int 			tmp_fd;
    int				read_bytes;
    int				total_bytes;
    int				bytes_to_read;
    char			*buffer;

    tmp_fd = open(name, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (tmp_fd <= 0)
        error_doom("couldn't open file");
    if (read(fd, &bytes_to_read, sizeof(bytes_to_read)) <= 0)
        error_doom("couldn't read bytes_to_read");
    if (!(buffer = malloc(1024)))
        error_doom("couldn't malloc buffer");
    total_bytes = 0;
    while (total_bytes < bytes_to_read)
    {
        read_bytes = read(fd, buffer, 1024);
        if (read_bytes <= 0)
            error_doom("rip");
        if (write(tmp_fd, buffer, 1024) != read_bytes)
            error_doom("oh no");
        total_bytes += read_bytes;
    }
    free(buffer);
    close(tmp_fd);
}
