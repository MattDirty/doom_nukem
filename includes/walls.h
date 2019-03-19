#ifndef DOOMNUKEM_WALLS_H
#define DOOMNUKEM_WALLS_H

#include "SDL.h"
#include "utils.h"

typedef struct			s_wall
{
    t_segment			segment;
    double				height; //debug
    SDL_Surface			*texture;
}						t_wall;

typedef struct			s_walls
{
    int					count;
    t_wall				 *items;
}						t_walls;

#endif
