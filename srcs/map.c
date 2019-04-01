#include <unistd.h>

#include "map.h"
#include "serialisation.h"

int		read_map_from_file(int fd, t_textures *textures, t_map **map)
{
    char *daysky;
    char *nightsky;

    if (!(*map = (t_map*)malloc(sizeof(t_map))))
        return (-1);

    if (read_sectors_from_file(fd, textures, &(*map)->sectors) < 0)
        return (-2);

    if (read_str_from_file(fd, &daysky) < 0)
        return (-3);

    if (read_str_from_file(fd, &nightsky) < 0)
        return (-4);

    if (find_texture_by_name(
            textures,
            daysky,
            &(*map)->daysky) < 0)
        return (-5);
    if (find_texture_by_name(
            textures,
            nightsky,
            &(*map)->nightsky) < 0)
        return (-6);

    return (0);
}

int		write_map_to_file(int fd, t_map *map)
{
    if (write_sectors_to_file(fd, map->sectors) < 0)
        return (-1);

    if (write_str_to_file(fd, map->daysky->userdata) < 0)
        return (-2);

    if (write_str_to_file(fd, map->nightsky->userdata) < 0)
        return (-3);

    return (0);
}
