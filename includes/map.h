#ifndef DOOMNUKEM_MAP_H
# define DOOMNUKEM_MAP_H

# include "sectors.h"

typedef struct			s_map
{
    t_sectors			*sectors;
    SDL_Surface         *daysky;
    SDL_Surface         *nightsky;
    enum e_bool         daytime;
}						t_map;

int		read_map_from_file(int fd, t_textures *textures, t_map **map);
int		write_map_to_file(int fd, t_map *map);

#endif
