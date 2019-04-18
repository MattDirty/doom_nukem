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

void        read_spawn_from_file(int fd, t_coords *spawn, int *index)
{
    if (read(fd, &(spawn->x), sizeof(spawn->x)) <= 0)
        error_doom("couldn't read player spawn coords");
    if (read(fd, &(spawn->y), sizeof(spawn->y)) <= 0)
        error_doom("couldn't read player spawn coords");
    if (read(fd, index, sizeof(*index)) <= 0)
        error_doom("Couldn't read player spawn index");
}

void        write_spawn_to_file(int fd, t_coords spawn, int index)
{
    if (write(fd, &(spawn.x), sizeof(spawn.x)) <= 0)
        error_doom("couldn't write player spawn coords");
    if (write(fd, &(spawn.y), sizeof(spawn.y)) <= 0)
        error_doom("couldn't write player spawn coords");
    if (write(fd, &(index), sizeof(index)) <= 0)
        error_doom("Couldn't write player spawn index");
}

void		read_map_from_file(int fd, t_textures *textures, t_map **map)
{
    if (!(*map = (t_map*)malloc(sizeof(t_map))))
        error_doom("couldn't malloc t_map");
    (*map)->daytime = 0;
    read_sectors_from_file(fd, textures, &(*map)->sectors);
    read_spawn_from_file(fd, &(*map)->spawn, &(*map)->player_spawn_index);
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
    find_texture_from_file(fd, textures, &(*map)->gun_sprites[3]);
    find_texture_from_file(fd, textures, &(*map)->gun_sprites[4]);
    find_texture_from_file(fd, textures, &(*map)->shotgun_sprites[0]);
    find_texture_from_file(fd, textures, &(*map)->shotgun_sprites[1]);
    find_texture_from_file(fd, textures, &(*map)->shotgun_sprites[2]);
    find_texture_from_file(fd, textures, &(*map)->vacuum_sprite);
    //find_texture_from_file(fd, textures, &(*map)->gun_to_pick);
    //find_texture_from_file(fd, textures, &(*map)->shotgun_to_pick);
    //find_texture_from_file(fd, textures, &(*map)->vacuum_to_pick);
}

void		write_map_to_file(int fd, t_map *map)
{
    write_sectors_to_file(fd, map->sectors);
    write_spawn_to_file(fd, map->spawn, map->player_spawn_index);
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
    write_str_to_file(fd, map->gun_sprites[3]->userdata);
    write_str_to_file(fd, map->gun_sprites[4]->userdata);
    write_str_to_file(fd, map->shotgun_sprites[0]->userdata);
    write_str_to_file(fd, map->shotgun_sprites[1]->userdata);
    write_str_to_file(fd, map->shotgun_sprites[2]->userdata);
    write_str_to_file(fd, map->vacuum_sprite->userdata);
    //write_str_to_file(fd, map->gun_to_pick->userdata);
    //write_str_to_file(fd, map->shotgun_to_pick->userdata);
    //write_str_to_file(fd, map->vacuum_to_pick->userdata);
}
