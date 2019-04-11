#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

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
