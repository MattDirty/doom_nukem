#ifndef DOOMNUKEM_PLAYER_H
# define DOOMNUKEM_PLAYER_H

# include "weapon.h"
# include "utils.h"
# include "map.h"
# include "SDL.h"
# include "config.h"

typedef struct			s_player
{
    t_coords	pos;
    double		heading;
    double		vision_height;
    t_vector    speed;
    t_weapons   weapons;
}						t_player;

t_player    init_player(t_config *op);
void    	clamp_player_values(t_player *p, t_config op);
void        move(t_player *p, t_map* map, const Uint8 *state, double time);
void        look_around(t_player *p, const Uint8 *state, double time);
#endif