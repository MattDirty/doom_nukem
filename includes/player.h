#ifndef DOOMNUKEM_PLAYER_H
# define DOOMNUKEM_PLAYER_H

# include "weapon.h"

typedef struct			s_player
{
    t_coords	pos;
    double		heading;
    double		vision_height;
    t_vector    speed;
    t_weapons   weapons;
}						t_player;

void init_player(t_player *p);

#endif