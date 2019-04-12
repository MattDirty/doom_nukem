#include <unistd.h>

#include "map.h"
#include "textures.h"
#include "serialisation.h"
#include "doom.h"

void		free_map(t_map *map)
{
    free_sectors(map->sectors);
    free(map);
}

void		read_map_from_file(int fd, t_textures *textures, t_map **map)
{
    if (!(*map = (t_map*)malloc(sizeof(t_map))))
        error_doom("couldn't malloc t_map");
    read_sectors_from_file(fd, textures, &(*map)->sectors);
    find_texture_from_file(fd, textures, &(*map)->daysky);
    find_texture_from_file(fd, textures, &(*map)->nightsky);
    find_texture_from_file(fd, textures, &(*map)->hud.sun);
    find_texture_from_file(fd, textures, &(*map)->hud.moon);
    find_texture_from_file(fd, textures, &(*map)->hud.cross[0]);
    find_texture_from_file(fd, textures, &(*map)->hud.cross[1]);
    find_texture_from_file(fd, textures, &(*map)->hud.cross[2]);
    find_texture_from_file(fd, textures, &(*map)->hud.bullet);
    find_texture_from_file(fd, textures, &(*map)->hud.happy_face);
    find_texture_from_file(fd, textures, &(*map)->hud.meh_face);
    find_texture_from_file(fd, textures, &(*map)->hud.sad_face);
    find_texture_from_file(fd, textures, &(*map)->hud.dead_face);
    find_texture_from_file(fd, textures, &(*map)->hud.badass_face);
    find_texture_from_file(fd, textures, &(*map)->hud.sehr_happy_face);
    find_texture_from_file(fd, textures, &(*map)->hud.hurt_face);
    find_texture_from_file(fd, textures, &(*map)->melee_sprite);
    find_texture_from_file(fd, textures, &(*map)->gun_sprites[0]);
    find_texture_from_file(fd, textures, &(*map)->gun_sprites[1]);
    find_texture_from_file(fd, textures, &(*map)->gun_sprites[2]);
}

void		write_map_to_file(int fd, t_map *map)
{
    write_sectors_to_file(fd, map->sectors);
    write_str_to_file(fd, map->daysky->userdata);
    write_str_to_file(fd, map->nightsky->userdata);
    write_str_to_file(fd, map->hud.sun->userdata);
    write_str_to_file(fd, map->hud.moon->userdata);
    write_str_to_file(fd, map->hud.cross[0]->userdata);
    write_str_to_file(fd, map->hud.cross[1]->userdata);
    write_str_to_file(fd, map->hud.cross[2]->userdata);
    write_str_to_file(fd, map->hud.bullet->userdata);
    write_str_to_file(fd, map->hud.happy_face->userdata);
    write_str_to_file(fd, map->hud.meh_face->userdata);
    write_str_to_file(fd, map->hud.sad_face->userdata);
    write_str_to_file(fd, map->hud.dead_face->userdata);
    write_str_to_file(fd, map->hud.badass_face->userdata);
    write_str_to_file(fd, map->hud.sehr_happy_face->userdata);
    write_str_to_file(fd, map->hud.hurt_face->userdata);
    write_str_to_file(fd, map->melee_sprite->userdata);
    write_str_to_file(fd, map->gun_sprites[0]->userdata);
    write_str_to_file(fd, map->gun_sprites[1]->userdata);
    write_str_to_file(fd, map->gun_sprites[2]->userdata);
}
