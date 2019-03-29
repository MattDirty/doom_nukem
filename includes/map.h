#ifndef DOOMNUKEM_MAP_H
#define DOOMNUKEM_MAP_H

#include "sectors.h"

typedef struct			s_map
{
    t_sectors			*sectors;
    SDL_Surface         *daysky;
}						t_map;

#endif
