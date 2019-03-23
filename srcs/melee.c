#include "animation.h"
#include "weapon.h"
#include "timer_handler.h"
#include "e_bool.h"

enum e_bool    unlock(const void *const ready)
{
    *(enum e_bool*)ready = t_true;
    return t_false;
}

void    melee_secondary(t_weapon *weapon, t_timer_handler *timer_handler)
{
    if (!weapon->secondary_ready)
        return;
    weapon->secondary_ready = t_false;
    add_event(
            timer_handler,
            weapon->secondary_cooldown,
            &unlock,
            &weapon->secondary_ready);
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
            &unlock,
            &weapon->main_ready);
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