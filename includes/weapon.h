#ifndef WEAPON_H
# define WEAPON_H

# include <SDL_mixer.h>
# include "e_bool.h"
# include "SDL.h"
# include "animation.h"
# include "config.h"
# include "timer_handler.h"

typedef struct  s_weapon
{
    SDL_Surface *sprite;
    Uint32      ammo;
    t_animation animation;
    void        (*main)();
    void        (*secondary)();
    double      main_cooldown;
    double      secondary_cooldown;
    enum e_bool main_ready;
    enum e_bool secondary_ready;
    Mix_Chunk   *main_sound;
    Mix_Chunk   *secondary_sound;
    enum e_bool usable;
}               t_weapon;

typedef struct  s_weapons
{
    t_weapon    *list;
    Uint8       size;
    Uint8       current;
}               t_weapons;

t_weapons   allocate_weapons(void);
void        draw_weapon(SDL_Surface *Surface, SDL_Surface *weapon, t_animation *animation, t_config *op);
void        melee_primary(t_weapon *weapon, t_timer_handler *timer_handler);
void        melee_secondary(t_weapon *weapon, t_timer_handler *timer_handler);

#endif
