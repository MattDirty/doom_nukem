#include "animation.h"
#include "weapon.h"

void    reset_animation(t_animation *animation)
{
    animation->x_offset = 0;
    animation->y_offset = 0;
    animation->x_resize = 1;
    animation->y_resize = 1;
    animation->state = 0;
    animation->end = 0;
}

void    start_animation(t_animation *animation, Uint32 end)
{
    animation->state = 0;
    animation->end = end;
}

void    animate(t_weapon *weapon, double ms_since_move)
{
    if (weapon->animation.end == 0
    || weapon->animation.state >= weapon->animation.end)
        return ;
    weapon->animation.state += ms_since_move;
    if (weapon->animation.state > weapon->animation.end)
        weapon->animation.state = weapon->animation.end;
    weapon->animation.animation_controller(&weapon->animation);
    if (weapon->animation.state == weapon->animation.end)
        reset_animation(&weapon->animation);
}
