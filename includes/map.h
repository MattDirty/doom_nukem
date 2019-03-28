#ifndef DOOMNUKEM_MAP_H
#define DOOMNUKEM_MAP_H

#include "sectors.h"

typedef struct			s_map
{
    t_sectors			*sectors;
    SDL_Surface         *skybox[6];
}						t_map;

#endif
