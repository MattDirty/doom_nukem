#include "doom.h"

void    draw_weapon(SDL_Surface *surface, SDL_Surface *weapon)
{
    int x;
    int y;

    y = 0;
    while (y < weapon->h)
    {
        x = 0;
        while (x < weapon->w)
        {
            put_pixel_alpha(surface, HALF_W - (weapon->w / 2) + x, WIN_H
                - weapon->h + y, get_pixel(weapon, x, y, t_false));
            x++;
        }
        y++;
    }
}