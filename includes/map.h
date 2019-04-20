#ifndef DOOMNUKEM_MAP_H
# define DOOMNUKEM_MAP_H

# include "sectors.h"

typedef struct          s_hud
{
    SDL_Surface         *sun;
    SDL_Surface         *moon;
    SDL_Surface         *cross[3];
    int                 id;
    SDL_Surface         *bullet;
    SDL_Surface         *happy_face;
    SDL_Surface         *meh_face;
    SDL_Surface         *sad_face;
    SDL_Surface         *dead_face;
    SDL_Surface         *badass_face;
    SDL_Surface         *sehr_happy_face;
    SDL_Surface         *hurt_face;
}                       t_hud;

typedef struct			s_map
{
    t_sectors			*sectors;
    t_coords            spawn;
    int     			player_spawn_index;
    SDL_Surface         *daysky;
    SDL_Surface         *nightsky;
    enum e_bool         daytime;
    t_hud               hud;
    SDL_Surface         *melee_sprite;
    SDL_Surface         *gun_sprites[5];
    SDL_Surface         *shotgun_sprites[3];
    SDL_Surface         *vacuum_sprite;
    SDL_Surface         *gun_to_pick;
    SDL_Surface         *shotgun_to_pick;
    SDL_Surface         *vacuum_to_pick;
}						t_map;

void		free_map(t_map *map);
void		read_map_from_file(int fd, t_textures *textures, t_map **map);
void		write_map_to_file(int fd, t_map *map);
void		write_hud_to_file(int fd, t_hud hud);
void		read_hud_from_file(int fd, t_textures *textures, t_hud *hud);
void		write_spawn_to_file(int fd, t_coords spawn, int index);
void		read_spawn_from_file(int fd, t_coords *spawn, int *index);

#endif
