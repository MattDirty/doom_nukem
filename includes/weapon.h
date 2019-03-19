#ifndef DOOMNUKEM_WEAPON_H
# define DOOMNUKEM_WEAPON_H

# include "e_bool.h"
# include "SDL.h"

typedef struct  s_weapon
{
    SDL_Surface *sprite;
    Uint32      ammo;
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
void        draw_weapon(SDL_Surface *Surface, SDL_Surface *weapon);

#endif
