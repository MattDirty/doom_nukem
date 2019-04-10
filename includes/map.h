#ifndef DOOMNUKEM_MAP_H
# define DOOMNUKEM_MAP_H

# include "sectors.h"

typedef struct          s_hud
{
    int                 id;
}                       t_hud;

typedef struct			s_map
{
    t_sectors			*sectors;
    SDL_Surface         *daysky;
    SDL_Surface         *nightsky;
    enum e_bool         daytime;
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
}						t_map;

int		read_map_from_file(int fd, t_textures *textures, t_map **map);
int		write_map_to_file(int fd, t_map *map);

#endif
