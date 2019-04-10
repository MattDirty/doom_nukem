#include <unistd.h>

#include "map.h"
#include "textures.h"
#include "serialisation.h"

int		read_map_from_file(int fd, t_textures *textures, t_map **map)
{
    if (!(*map = (t_map*)malloc(sizeof(t_map))))
        return (-1);
    if (read_sectors_from_file(fd, textures, &(*map)->sectors) < 0)
        return (-2);
    if (find_texture_from_file(fd, textures, &(*map)->daysky) < 0)
        return (-3);
    if (find_texture_from_file(fd, textures, &(*map)->nightsky) < 0)
        return (-4);
    if (find_texture_from_file(fd, textures, &(*map)->sun) < 0)
        return (-5);
    if (find_texture_from_file(fd, textures, &(*map)->moon) < 0)
        return (-6);
    if (find_texture_from_file(fd, textures, &(*map)->cross[0]) < 0)
        return (-7);
    if (find_texture_from_file(fd, textures, &(*map)->cross[1]) < 0)
        return (-8);
    if (find_texture_from_file(fd, textures, &(*map)->cross[2]) < 0)
        return (-9);
    if (find_texture_from_file(fd, textures, &(*map)->bullet) < 0)
        return (-10);
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
    if (write_str_to_file(fd, map->sun->userdata) < 0)
        return (-4);
    if (write_str_to_file(fd, map->moon->userdata) < 0)
        return (-5);
    if (write_str_to_file(fd, map->cross[0]->userdata) < 0)
        return (-6);
    if (write_str_to_file(fd, map->cross[1]->userdata) < 0)
        return (-7);
    if (write_str_to_file(fd, map->cross[2]->userdata) < 0)
        return (-8);
    if (write_str_to_file(fd, map->bullet->userdata) < 0)
        return (-9);
    return (0);
}
