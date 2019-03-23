#include "animation.h"
#include <stdio.h>
void    melee_primary(t_animation *animation)
{
    start_animation(animation, 400);
}

void    melee_primary_animation(t_animation *animation)
{
    int step;
    int value;

    step = animation->state / (animation->duration / 4);
    value = animation->state % (animation->duration / 4);
    if (step == 0)
        animation->x_offset = -value;
    if (step == 1)
        animation->x_offset = -(animation->duration / 4) + value;
    if (step == 2)
        animation->x_offset = value;
    if (step == 3)
        animation->x_offset = animation->duration / 4 - value;
}