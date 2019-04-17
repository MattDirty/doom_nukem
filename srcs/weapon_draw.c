#include "surface_manipulation.h"
#include "animation.h"
#include "config.h"

void    draw_weapon(SDL_Surface *surface, SDL_Surface *weapon, t_animation *animation, t_config *op)
{
    int x;
    int y;

    y = 0;
    while (y < weapon->h)
    {
        x = 0;
        while (x < weapon->w)
        {
            put_pixel_alpha(surface,
                    (op->half_w - (weapon->w / 2)) + x + animation->x_offset,
                    (op->win_h - weapon->h) + y + animation->y_offset,
                    get_pixel(weapon, x, y, e_false));
            x++;
        }
        y++;
    }
}