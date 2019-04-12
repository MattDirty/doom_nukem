#ifndef WEAPON_H
# define WEAPON_H

# include <SDL_mixer.h>
# include "e_bool.h"
# include "SDL.h"
# include "animation.h"
# include "config.h"
# include "timer_handler.h"
# include "map.h"

typedef struct  s_weapon
{
    SDL_Surface *sprite_current;
    SDL_Surface **sprites;
    Uint32      sprites_count;
    Uint32      sprite_fire_current;
    SDL_Surface **sprites_fire;
    Uint32      sprites_fire_count;
    Uint32      sprite_cooldown_current;
    SDL_Surface **sprites_cooldown;
    Uint32      sprites_cooldown_count;
    Uint32      ammo;
    t_animation animation;
    void        (*main)();
    double      main_cooldown;
    enum e_bool main_ready;
    Mix_Chunk   *main_sound;
    enum e_bool usable;
}               t_weapon;

typedef struct  s_weapons
{
    t_weapon            item;
    struct s_weapons    *next;
}               t_weapons;

t_weapons   *allocate_weapons(t_map *map);
void        draw_weapon(SDL_Surface *Surface, SDL_Surface *weapon, t_animation *animation, t_config *op);
void        melee_primary(t_weapon *weapon, t_timer_handler *timer_handler);

#endif
