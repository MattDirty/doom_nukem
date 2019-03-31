#ifndef DOOMNUKEM_WALLS_H
# define DOOMNUKEM_WALLS_H

# include "SDL.h"
# include "utils.h"
# include "e_bool.h"

typedef struct s_sector t_sector;

typedef struct  s_link
{
    t_sector    *sector1;
    t_sector    *sector2;
}               t_link;

enum            e_wall_type
{
    portal,
    wall
};

union   u_pointer
{
    SDL_Surface *texture;
    t_link      sector;
};

typedef struct			s_wall
{
    t_segment			segment;
    double				height; //debug
    union u_pointer     pointer;
    enum e_wall_type    type;
}						t_wall;

typedef struct			s_walls
{
    int					count;
    t_wall				**items;
}						t_walls;

#endif
