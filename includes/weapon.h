#ifndef WEAPON_H
# define WEAPON_H

# include <SDL_mixer.h>
# include "e_bool.h"
# include <SDL.h>
# include "animation.h"
# include "config.h"
# include "timer_handler.h"
# include "map.h"
# include "sounds.h"

typedef struct  s_player t_player;
typedef struct  s_env t_env;

typedef struct  s_weapon
{
    SDL_Surface *sprite_current;
    SDL_Surface *sprites[3];
    t_animation animation;
    SDL_Surface *sprites_fire;
    SDL_Surface *sprites_cooldown;
    int         ammo;
    t_animation main_animation;
    void        (*main)();
    double      main_cooldown;
    enum e_bool main_ready;
    Mix_Chunk   *main_sound;
    double      range;
    Uint32      scatter;
    double      scatter_angle;
    Uint32      damage;
    enum e_bool usable;
}               t_weapon;

typedef struct  s_weapons
{
    t_weapon            *item;
    struct s_weapons    *next;
}               t_weapons;

typedef struct  s_weapon_and_timer
{
    t_weapon        *weapon;
    t_timer_handler *timer_handler;
}               t_weapon_and_timer;

t_weapons   *allocate_weapons(t_sounds *sounds, t_map *map);
void		free_weapons(t_weapons *weapons);
void        draw_weapon(SDL_Surface *Surface, SDL_Surface *weapon, t_animation *animation, t_config *op);
t_weapon    *get_weapon(t_weapons *node, Uint32 target);
enum e_bool unlock(double ms_since_update, t_params ready);
void        weapon_ray_fire(t_env *e, t_timer_handler *timer_handler);
void        put_weapon(t_weapons *node, t_weapon *weapon, Uint32 target);
void		make_weapon_usable(t_weapons *node, Uint32 target);


#endif
