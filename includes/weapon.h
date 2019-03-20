#ifndef DOOMNUKEM_WEAPON_H
# define DOOMNUKEM_WEAPON_H

# include "e_bool.h"
# include "SDL.h"
# include "animation.h"
# include "config.h"

typedef struct  s_weapon
{
    SDL_Surface *sprite;
    Uint32      ammo;
    t_animation animation;
    void        (*main)();
    void        (*secondary)();
    enum e_bool usable;
}               t_weapon;

typedef struct  s_weapons
{
    t_weapon    *list;
    Uint8       size;
    Uint8       current;
}               t_weapons;

t_weapons   allocate_weapons();
void        draw_weapon(SDL_Surface *Surface, SDL_Surface *weapon, t_animation *animation, t_config *op);
void        animate(t_weapon *weapon, double ms_since_move);
void        melee_primary(t_animation *a);
void        melee_primary_animation(t_animation *a);
#endif
