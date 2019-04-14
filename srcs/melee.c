#include "animation.h"
#include "weapon.h"
#include "timer_handler.h"
#include "e_bool.h"
#include "doom.h"

enum e_bool    melee_primary_animation(
        double ms_since_update,
        t_params pointer)
{
    int step;
    int value;
    t_animation *animation;

    animation = (t_animation*)pointer;
    animation->time += ms_since_update;

    step = (int)(animation->time) / (int)(animation->duration / 4);
    value = (int)(animation->time) % (int)(animation->duration / 4);
    if (step == 0)
        animation->x_offset = -value;
    if (step == 1)
        animation->x_offset = -(animation->duration / 4) + value;
    if (step == 2)
        animation->x_offset = value;
    if (step == 3)
        animation->x_offset = animation->duration / 4 - value;
    if (step > 3)
        animation->x_offset = 0;

    return (animation->time <= animation->duration);
}

void    melee_primary(t_env *e, t_timer_handler *timer_handler)
{
    t_weapon    *weapon;

    weapon = e->p.weapon;
    if (!weapon->main_ready)
        return;
    reset_animation(&weapon->main_animation);
    start_animation(&weapon->main_animation, 400);
    add_event(timer_handler, 5,&melee_primary_animation,
            &weapon->main_animation);
    Mix_PlayChannel(-1, weapon->main_sound, 0);
    weapon->main_ready = t_false;
    add_event(timer_handler, weapon->main_cooldown,
            &unlock,&weapon->main_ready);
    weapon_ray_fire(e, timer_handler);
}

t_weapon    *load_melee(t_sounds *sounds, t_map *map)
{
    t_weapon    *weapon;

    if (!(weapon = (t_weapon *)malloc(sizeof(t_weapon))))
        error_doom("Couldn't malloc melee");
    weapon->sprites_count = 1;
    if (!(weapon->sprites = (SDL_Surface **)malloc(sizeof(SDL_Surface *)
            * weapon->sprites_count)))
        error_doom("Couldn't malloc melee.sprites");
    weapon->sprites[0] = map->melee_sprite;
    weapon->sprites_cooldown = NULL;
    weapon->sprites_fire = NULL;
    weapon->sprite_current = weapon->sprites[0];
    weapon->ammo = -1;
    weapon->main = NULL;
    weapon->usable = t_true;
    weapon->damage = 99;
    weapon->range = 0.5;
    weapon->scatter = 1;
    weapon->scatter_angle = 1;
    reset_animation(&weapon->main_animation);
    weapon->main = melee_primary;
    weapon->main_cooldown = 2000;
    weapon->main_ready = t_true;
    if (!(weapon->main_sound = sounds->fu_bitch))
        error_doom("Can't load weapon sound ...");
    return (weapon);
}
