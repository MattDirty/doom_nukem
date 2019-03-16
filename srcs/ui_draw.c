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

void    draw_crosshair(SDL_Surface *surface, Uint32 color)
{
    t_segment   segment;

    segment.x1 = HALF_W;
    segment.y1 = HALF_H - 30;
    segment.x2 = HALF_W;
    segment.y2 = HALF_H - 30 - 50;
    draw_segment(surface, segment, color);
    segment.x1 = HALF_W - 30;
    segment.y1 = HALF_H;
    segment.x2 = HALF_W - 30 - 50;
    segment.y2 = HALF_H;
    draw_segment(surface, segment, color);
    segment.x1 = HALF_W;
    segment.y1 = HALF_H + 30;
    segment.x2 = HALF_W;
    segment.y2 = HALF_H + 30 + 50;
    draw_segment(surface, segment, color);
    segment.x1 = HALF_W + 30;
    segment.y1 = HALF_H;
    segment.x2 = HALF_W + 30 + 50;
    segment.y2 = HALF_H;
    draw_segment(surface, segment, color);
    put_pixel_alpha(surface, HALF_W, HALF_H, color);
}

void    ui_draw(t_sdl *sdl, SDL_Surface *weapon)
{
    draw_crosshair(sdl->surface, CROSSHAIR_COLOR);
    draw_weapon(sdl->surface, weapon);
}