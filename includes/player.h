#ifndef DOOMNUKEM_PLAYER_H
# define DOOMNUKEM_PLAYER_H

# include "weapon.h"
# include "utils.h"
# include "map.h"
# include "SDL.h"
# include "config.h"

typedef struct          s_jump
{
    double              height;
    double              gravity;
    enum e_bool         ready;
    double              duration;
    double              time;
}                       t_jump;

typedef struct			s_player
{
	t_sector	*current_sector;
    t_coords	pos;
    double		heading;
    double		vision_height;
    double		speed_factor;
    t_vector    speed;
    t_weapons   weapons;
    t_jump      jump;
    enum e_bool dead;
    Uint32      health;
}						t_player;

t_player    init_player(t_config *op, t_sector *starting_sector);
void    	clamp_player_values(t_player *p, t_config op);
void		move(t_player *p, const Uint8 *state, double time);
void        look_around(t_player *p, const Uint8 *state, double time);
enum e_bool jumping(double ms_since_update, t_params pointer);
void        game_over(SDL_Surface *surface, t_config *op);
void        hurt_or_heal(t_player *p, const Uint8 *state, double time);

#endif