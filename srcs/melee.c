#include "animation.h"
#include "weapon.h"
#include "timer_handler.h"
#include "e_bool.h"
#include "doom.h"

enum e_bool    unlock(double ms_since_update, t_params ready)
{
    (void)ms_since_update;
    *(enum e_bool*)ready = t_true;
    return (t_false);
}

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

void    melee_primary(t_weapon *weapon, t_timer_handler *timer_handler)
{
    if (!weapon->main_ready || !weapon->ammo)
        return;

    reset_animation(&weapon->animation);
    start_animation(&weapon->animation, 400);
    add_event(
            timer_handler,
            5,
            &melee_primary_animation,
            &weapon->animation);
    Mix_PlayChannel(-1, weapon->main_sound, 0);
    weapon->main_ready = t_false;
    weapon->ammo--;
    add_event(
            timer_handler,
            weapon->main_cooldown,
            &unlock,
            &weapon->main_ready);
}

t_weapon    load_melee(t_map *map)
{
    t_weapon    weapon;

    weapon.sprites_count = 1;
    if (!(weapon.sprites = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * weapon.sprites_count)))
        error_doom("Couldn't malloc gun.sprites");
    weapon.sprites[0] = map->melee_sprite;
    weapon.ammo = 10;
    weapon.main = NULL;
    weapon.usable = t_true;
    reset_animation(&weapon.animation);
    weapon.main = melee_primary;
    weapon.main_cooldown = 2000;
    weapon.main_ready = t_true;
    if (!(weapon.main_sound = Mix_LoadWAV("sounds/fu_bitch.wav")))
        error_doom("Can't load weapon sound ...");
    return (weapon);
}
