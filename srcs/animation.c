#include "animation.h"
#include "weapon.h"

void    reset_animation(t_animation *animation)
{
    animation->x_offset = 0;
    animation->y_offset = 0;
    animation->x_resize = 1;
    animation->y_resize = 1;
    animation->time = 0;
    animation->duration = 0;
}

void    start_animation(t_animation *animation, Uint32 duration)
{
    animation->time = 0;
    animation->duration = duration;
}

void    animate(t_weapon *weapon, double ms_since_move)
{
    if (weapon->animation.duration == 0
    || weapon->animation.time >= weapon->animation.duration)
        return ;
    weapon->animation.time += ms_since_move;
    if (weapon->animation.time > weapon->animation.duration)
        weapon->animation.time = weapon->animation.duration;
    weapon->animation.animation_controller(&weapon->animation);
    if (weapon->animation.time == weapon->animation.duration)
        reset_animation(&weapon->animation);
}
