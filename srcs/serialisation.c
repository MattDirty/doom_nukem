#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft.h"

#include "serialisation.h"

int	read_file(char *filename, t_textures **textures, t_map **map)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd <= 0)
        return (-1);

    if (read_textures_from_file(fd, textures) < 0)
        return (-2);

    if (read_map_from_file(fd, *textures, map) < 0)
        return (-3);

    return (0);
}

int	write_file(char *filename, t_textures *textures, t_map *map)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT, 777);
    if (fd <= 0)
        return (-1);

    if (write_textures_to_file(fd, textures) < 0)
        return (-2);

    if (write_map_to_file(fd, map) < 0)
        return (-3);

    return (0);
}

int	read_str_from_file(int fd, char **name)
{
    char			*c;

    c = ft_strnew(1);
    *name = ft_strnew(1);

    while (1)
    {
        if (read(fd, c, sizeof(char)) <= 0)
        {
            free(c);
            return (-1);
        }

        *name = ft_strjoin(*name, c);

        if (!*c)
        {
            free(c);
            return (0);
        }
    }
}

int	write_str_to_file(int fd, char *name)
{
    char			*c;
    int				i;

    if (!name)
        return(-1);

    i = 0;
    while (1)
    {
        c = name + i++;

        write(fd, c, sizeof(char));
        if (!*c)
            return (0);
    }
    exit(0);
}
