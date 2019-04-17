#ifndef DOOMNUKEM_ANIMATION_H
# define DOOMNUKEM_ANIMATION_H

# include <SDL.h>

typedef struct  s_animation
{
    int     x_offset;
    int     y_offset;
    double  x_resize;
    double  y_resize;
    double  duration;
    double  time;
}               t_animation;

void    reset_animation(t_animation *animation);
void    start_animation(t_animation *animation, Uint32 duration);

#endif
