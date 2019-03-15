#include "doom.h"

void    print_t_color(t_color color)
{
    //debug
    printf("A:%d R:%d G:%d B:%d\n", color.alpha, color.red, color.green, color.blue);
}

t_color	int_to_t_color(Uint32 color)
{
    t_color new_struct;

    new_struct.alpha = (color & MASK_ALPHA) >> 24;
    new_struct.red = (color & MASK_RED) >> 16;
    new_struct.green = (color & MASK_GREEN) >> 8;
    new_struct.blue = (color & MASK_BLUE);
    return (new_struct);
}

Uint32	t_color_to_int(t_color color)
{
    Uint32	i_color;

    i_color = (color.alpha << 24) + (color.red << 16) + (color.green << 8) + (color.blue);
    return (i_color);
}

t_color	create_argb(Uint8 alpha, Uint8 red, Uint8 green, Uint8 blue)
{
    t_color	color;

    color.alpha = alpha;
    color.red = red;
    color.green = green;
    color.blue = blue;
    return (color);
}