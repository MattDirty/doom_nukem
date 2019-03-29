#ifndef DOOMNUKEM_MAP_H
#define DOOMNUKEM_MAP_H

#include "sectors.h"

typedef struct			s_map
{
    t_sectors			*sectors;
    SDL_Surface         *daysky;
    SDL_Surface         *nightsky;
    enum e_bool         daytime;
}						t_map;

#endif
