#include "animation.h"
#include "weapon.h"
#include "timer_handler.h"

void    unlock_secondary(const void *const weapon)
{
    ((t_weapon*)weapon)->secondary_ready = t_true;
}

void    unlock_main(const void *const weapon)
{
    ((t_weapon*)weapon)->main_ready = t_true;
}

void    melee_secondary(t_weapon *weapon, t_timer_handler *timer_handler)
{
    if (!weapon->secondary_ready)
        return;
    printf("j'ai mis mon penis dans la mayo help\n");
    weapon->secondary_ready = t_false;
    add_event(
            timer_handler,
            weapon->secondary_cooldown,
            &unlock_secondary,
            weapon);
}

void    melee_primary(t_weapon *weapon, t_timer_handler *timer_handler)
{
    if (!weapon->main_ready)
        return;
    start_animation(&weapon->animation, 400);
    weapon->main_ready = t_false;
    add_event(
            timer_handler,
            weapon->main_cooldown,
            &unlock_main,
            weapon);
}

void    melee_primary_animation(t_animation *animation)
{
    int step;
    int value;

    step = animation->time / (animation->duration / 4);
    value = animation->time % (animation->duration / 4);
    if (step == 0)
        animation->x_offset = -value;
    if (step == 1)
        animation->x_offset = -(animation->duration / 4) + value;
    if (step == 2)
        animation->x_offset = value;
    if (step == 3)
        animation->x_offset = animation->duration / 4 - value;
}