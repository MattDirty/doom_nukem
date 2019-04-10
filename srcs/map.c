#include <unistd.h>

#include "map.h"
#include "textures.h"
#include "serialisation.h"

int		read_map_from_file(int fd, t_textures *textures, t_map **map)
{
    if (!(*map = (t_map*)malloc(sizeof(t_map))))
        return (-1);
    printf("trying to read sectors\n");
    if (read_sectors_from_file(fd, textures, &(*map)->sectors) < 0)
        return (-2);
    printf("managed to read sectors\n");
    if (find_texture_from_file(fd, textures, &(*map)->daysky) < 0)
        return (-3);
    if (find_texture_from_file(fd, textures, &(*map)->nightsky) < 0)
        return (-4);
    if (find_texture_from_file(fd, textures, &(*map)->hud.sun) < 0)
        return (-5);
    if (find_texture_from_file(fd, textures, &(*map)->hud.moon) < 0)
        return (-6);
    if (find_texture_from_file(fd, textures, &(*map)->hud.cross[0]) < 0)
        return (-7);
    if (find_texture_from_file(fd, textures, &(*map)->hud.cross[1]) < 0)
        return (-8);
    if (find_texture_from_file(fd, textures, &(*map)->hud.cross[2]) < 0)
        return (-9);
    if (find_texture_from_file(fd, textures, &(*map)->hud.bullet) < 0)
        return (-10);
    if (find_texture_from_file(fd, textures, &(*map)->hud.happy_face) < 0)
        return (-11);
    if (find_texture_from_file(fd, textures, &(*map)->hud.meh_face) < 0)
        return (-12);
    if (find_texture_from_file(fd, textures, &(*map)->hud.sad_face) < 0)
        return (-13);
    if (find_texture_from_file(fd, textures, &(*map)->hud.dead_face) < 0)
        return (-14);
    if (find_texture_from_file(fd, textures, &(*map)->hud.badass_face) < 0)
        return (-15);
    if (find_texture_from_file(fd, textures, &(*map)->hud.sehr_happy_face) < 0)
        return (-16);
    if (find_texture_from_file(fd, textures, &(*map)->hud.hurt_face) < 0)
        return (-17);
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
    if (write_str_to_file(fd, map->hud.sun->userdata) < 0)
        return (-4);
    if (write_str_to_file(fd, map->hud.moon->userdata) < 0)
        return (-5);
    if (write_str_to_file(fd, map->hud.cross[0]->userdata) < 0)
        return (-6);
    if (write_str_to_file(fd, map->hud.cross[1]->userdata) < 0)
        return (-7);
    if (write_str_to_file(fd, map->hud.cross[2]->userdata) < 0)
        return (-8);
    if (write_str_to_file(fd, map->hud.bullet->userdata) < 0)
        return (-9);
    if (write_str_to_file(fd, map->hud.happy_face->userdata) < 0)
        return (-10);
    if (write_str_to_file(fd, map->hud.meh_face->userdata) < 0)
        return (-11);
    if (write_str_to_file(fd, map->hud.sad_face->userdata) < 0)
        return (-12);
    if (write_str_to_file(fd, map->hud.dead_face->userdata) < 0)
        return (-13);
    if (write_str_to_file(fd, map->hud.badass_face->userdata) < 0)
        return (-14);
    if (write_str_to_file(fd, map->hud.sehr_happy_face->userdata) < 0)
        return (-15);
    if (write_str_to_file(fd, map->hud.hurt_face->userdata) < 0)
        return (-16);
    return (0);
}
